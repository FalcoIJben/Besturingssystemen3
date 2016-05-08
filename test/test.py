from subprocess import Popen, PIPE, STDOUT


FILE_PATH = './main'

def test_echo():
    print('----------')
    print('testing echo')
    print('using command "echo test"')

    shell = Popen(FILE_PATH, stdout=PIPE, stdin=PIPE, stderr=STDOUT)
    test_1 = shell.communicate(input=b'echo test\n')[0]
    output = test_1.decode()

    print('OUTPUT')
    print('----------')
    print(output)
    assert 'SHELL: test' in output

# test the pipe function by echoing test and using it as input for cat
def test_pipe():
    print('----------')
    print('testing pipe')
    shell = Popen(FILE_PATH, stdout=PIPE, stdin=PIPE, stderr=STDOUT)
    input = b'echo test | cat'

    print('using command: ', str(input))

    test_1 = shell.communicate(input=input)[0]
    output = test_1.decode()

    print('OUTPUT')
    print('----------')
    print(output)
    assert 'SHELL: test' in output



def test_sequence():
    print('----------')
    print('testing sequence')

    shell = Popen(FILE_PATH, stdout=PIPE, stdin=PIPE, stderr=STDOUT)
    input = b'echo test; echo test'
    test_1 = shell.communicate(input=input)[0]
    print('using command: ', str(input))
    output = test_1.decode()

    print('OUTPUT')
    print('----------')
    print(output)

    # the first is test with shell
    output_lines = output.splitlines()
    assert output_lines[0] == 'SHELL: test'
    # this is just test because of chaining
    assert output_lines[1] == 'test'




try:
    test_echo()
    test_pipe()
    test_sequence()
    test_output_append()

    print('TEST SUCCESS')
except Exception:
    print('TEST FAILED')
    raise
