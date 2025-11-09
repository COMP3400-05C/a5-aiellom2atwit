#!/usr/bin/env bats
load 'test_helpers'


setup() {
    export BATS_TEST_TIMEOUT=10
}

@test "partc" {
    run partc

    assert_output "USAGE: partc FILEIN"                     # Assert if output matches
    assert [ "$status" -eq 1 ]                              # Assert if exit status was 1
}
@test "partc tests/file1.txt" {
    run partc "tests/file1.txt"

    cat << EOF | assert_output -                            # Assert if output matches
Number,0
Other,0
Upper,1
Space,9
Lower,34
EOF
}
@test "partc tests/file2.txt" {
    run partc "tests/file2.txt"

    cat << EOF | assert_output -                            # Assert if output matches
Number,0
Other,20
Upper,26
Space,147
Lower,539
EOF
}

