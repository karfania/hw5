## HW 5

 - Name: Kourosh Arfania
 - Email: arfania@usc.edu

### Checkpoint 1 Notes

#### Compiling the Code:

- Enter docker container (`ch start csci104` -> `ch shell csci104`) or use Codio and navigate to `hw5/`

##### wordle
(1) Ensure you are in the `hw5` directory

(2) Run `make wordle-driver` to compile and link all files for the wordle code

(3) Enter `./wordle -i-- dn` in your terminal to run the basic tests provided in the Codio guide

(4) Enter `cd hw5_tests/wordle_tests/`, `make wordle_tests`, and `./wordle_tests` run more comprehensive tests

(5) Run `valgrind --tool=memcheck --leak-check=yes ./wordle_tests` to check for memory loss/leaks

### Final Submission Notes
##### schedwork
(1) Ensure you are in the `hw5` directory

(2) Run `make schedwork-driver` to compile and link all files for the schedwork code

(3) Enter `./schedwork-driver` in your terminal to run the basic tests provided in the Codio guide

(4) Enter `cd hw5_tests/schedwork_tests/`, `make schedwork_tests`, and `./schedwork_tests` run more comprehensive tests

(5) Run `valgrind --tool=memcheck --leak-check=yes ./schedwork_tests` to check for memory loss/leaks
