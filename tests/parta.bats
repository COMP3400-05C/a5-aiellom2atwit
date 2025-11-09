#!/usr/bin/env bats
load 'test_helpers'


setup() {
    export BATS_TEST_TIMEOUT=10
}

@test "parta" {
    run parta

    assert_output "USAGE: parta FILEIN"                     # Assert if output matches
    assert [ "$status" -eq 1 ]                              # Assert if exit status was 1
}
@test "parta tests/file1.txt" {
    run parta "tests/file1.txt"

    cat << EOF | assert_output -                            # Assert if output matches
Upper,1
Lower,34
Number,0
Space,9
Other,0
EOF
    assert [ "$status" -eq 0 ]                              # Assert if exit status was 0
}

@test "parta tests/file2.txt" {
    run parta "tests/file2.txt"

    cat << EOF | assert_output -                            # Assert if output matches
Upper,26
Lower,539
Number,0
Space,147
Other,20
EOF

    assert [ "$status" -eq 0 ]                              # Assert if exit status was 0
}
@test "parta tests/this_file_doesnt_exist.txt" {
    run parta tests/this_file_doesnt_exist.txt

    assert_output "ERROR: tests/this_file_doesnt_exist.txt not found" # Assert if output matches
    assert [ "$status" -eq 2 ]                              # Assert if exit status was 2
}
