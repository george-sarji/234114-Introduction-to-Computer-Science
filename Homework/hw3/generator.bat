for /L %%i in (1, 1, 20) DO (
    test-gen.exe >> ./Tests/test_%%i.txt
    hw3q1.exe < ./Tests/test_%%i.txt > ./Tests/test_output_%%i.txt
)