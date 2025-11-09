#!/usr/bin/env bash

# Determine the absolute path to this script's directory
TEST_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Paths to bats-support and bats-assert
SUPPORT_DIR="${TEST_DIR}/bats-support"
ASSERT_DIR="${TEST_DIR}/bats-assert"

# Verify that both dependencies exist
if [ ! -d "$SUPPORT_DIR" ] || [ ! -d "$ASSERT_DIR" ]; then
  echo "ERROR: Could not find bats-support or bats-assert directories in ${TEST_DIR}" >&2
  exit 1
fi

# Load bats-support and bats-assert
load "${SUPPORT_DIR}/load.bash"
load "${ASSERT_DIR}/load.bash"

# Add both build/ and project root to PATH
PATH="${PROJECT_ROOT}/build:${PROJECT_ROOT}:$PATH"
export PATH

# Optional global test timeout
export BATS_TEST_TIMEOUT=10