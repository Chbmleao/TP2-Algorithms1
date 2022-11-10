####### Run the tests with this script #######

# Test files are trivial_input.txt, small_input.txt, medium_input.txt and big_input.txt inside the test_files folder
# The binary file is called "tp02"

# The corret output files are trivial_output.txt, small_output.txt, medium_output.txt and big_output.txt
# The timeout is 30 seconds (about 3 seconds per case)

# clean the output files
rm -f trivial_input.txt.out small_input.txt.out medium_input.txt.out big_input.txt.out

for i in trivial_input.txt small_input.txt medium_input.txt big_input.txt
do
    echo -n "Running test $i ... "

    timeout 70 ./tp02 < test_files/$i > $i.out
    if [ $? -eq 124 ]
    then
        echo "---> Timeout"
    else
        diff -q $i.out test_files/${i/input/output}
        if [ $? -eq 0 ]
        then
            echo "---> Passed!"
        else
            echo "---> Failed :/"
        fi
    fi
done