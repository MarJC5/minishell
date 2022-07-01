# Command in PATH
date

# Command with absolute path given
/bin/date
/Users/tanguy/bin/nvim


# Command with relative path given
./test.out
../../../../bin/date
test_dir/test.out

# Commands with no permissions to execute
chmod -x test.out; test.out


# Command in an inaccessible folder
chmod 000 test_dir; test_dir/test.out

# Shell expansions
echo $HOME/Documents
echo '$HOME/Documents'
echo "$HOME/Documents"
echo '"$HOME/Documents"'
echo "'$HOME/Documents'"
echo "$HOM"
echo $HOM
echo '$HOM'
echo $?
echo ~
echo '~'
echo "~"

# More quote testing !
"/bin/"date
'/bin/'date

# builtins
echo "Hello"
echo "Hello" "How are you" "Fine and you ?" | cat -e
echo -n "Hello" "How are you" "Fine and you ?" | cat -e
echo
echo -n

pwd
pwd asdf

cd
cd asdf
cd test_dir
chmod -x test_dir/; cd test_dir
cd /Users/tanguy
cd dir1 dir2

exit
exit 0
exit 1
exit a
exit 1a
exit 0 1

env
env asdf
export TEST_VAR
export TEST_VAR=Hello
export TEST_VAR2="Hello2"
export TEST_VAR3="Home is $HOME"

unset TEST_VAR
unset TEST_VAR2 TEST_VAR3

# Output Redirections
echo "Hi" > test.txt
echo "Hi again" >> test.txt
> test.txt echo "Hello"
>> test.txt echo "Hello again"

# Input Redirections
cat < test.txt
< test.txt cat
cat < file_doesnt_exist

# Heredoc
cat << aaa
# Check with 'aa', 'aaa', 'aaaa'

# Pipes
ls | wc -l
ls | grep "Makefile" | wc -c
date | exit
exit | date
cat | date
echo Hi |
| echo Hi
echo "Hi" | | cat

# Random
echo "Hi" > test.txt | cat -e

# Signals
cat
