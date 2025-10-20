from invoke import task
from pathlib import Path
import subprocess


@task(
    iterable=["D", "check"],
    help={
        "D": "Pass cache variables to cmake (use None to unset)",
        "checks": "Enable/disable clang-tidy checks (implies tidy)",
        "echo": "Echo the CMake command before executing",
        "force": "Use a fresh CMake cache",
        "tidy": "Use clang-tidy to analyze code",
    },
)
def cmake(context, D=None, checks=None, echo=False, force=False, tidy=False):
    """Generate make files to build the project"""
    # Internal defaults
    command = [
        "cmake",
        "-S",
        "./",
        "-B",
        "./build/",
    ]
    cache = {
        "CMAKE_BUILD_TYPE": "Release",
        "CMAKE_INSTALL_PREFIX": "./install/",
    }

    # Collect user cache overrides
    # Key may contain type
    user_cache = {}
    if D is None:
        D = []
    for option in D:
        if "=" not in option:
            raise RuntimeError(f"Invalid option not in KEY=VALUE form: {option}")
        key, value = option.split("=", 1)
        if value == "None" or value == "":
            value = None
        user_cache[key] = value

    # Keep default cache variables NOT overridden by user
    # Compare without types, if present
    cache = {
        key: value
        for key, value in cache.items()
        if not any(
            (
                key in user_cache,
                ":" in key and key.split(":", 1)[0] in user_cache,
                any(":" in k and key == k.split(":", 1)[0] for k in user_cache),
            )
        )
    }

    # Add user-overrides
    for key, value in user_cache.items():
        if value is not None:
            cache[key] = value

    # Enable clang-tidy checks
    tidy_checks = [
        "bugprone-*",
        "cppcoreguidelines-*",
        "clang-analyzer-*",
        "misc-*",
        "modernize-*",
        "performance-*",
        "readability-*",
    ]

    if checks:
        tidy = True
        tidy_checks = [group for group in tidy_checks if f"-{group}" not in checks]
        tidy_checks.extend(checks)

    if tidy:
        gcc_toolchain = Path(
            subprocess.run(
                ["which", "gcc"], capture_output=True, text=True, check=True
            ).stdout
        ).parent.parent
        tidy_checks = ["--checks=-*", *tidy_checks]
        tidy_command = (
            "clang-tidy",
            "--header-filter=.*",
            f"--extra-arg=--gcc-toolchain={gcc_toolchain}",
            ",".join(tidy_checks),
        )
        cache["CMAKE_CXX_CLANG_TIDY"] = f'"{";".join(tidy_command)}"'

    command.extend([f"-D {key}={value}" for key, value in cache.items()])

    if force:
        command.append("--fresh")

    context.run(" ".join(command), echo=echo, pty=True)


@task
def make(context, echo=False, jobs=None, targets=None, verbose=False):
    """Build the project"""
    command = ["cmake", "--build", "./build/"]

    if not targets:
        targets = ["all"]
    command.extend(["--target", *targets])

    if jobs:
        command.extend(["--jobs", jobs])

    if verbose:
        command.append("--verbose")

    context.run(" ".join(command), echo=echo, pty=True)
