# database-normalizer

Normalize databases up to 5NF based on a SQL dataset and the functional dependencies

## Program Requirements

Run the makefileDependencies file to determine installation steps

```bash
    bash makefileDependencies.sh
```

## Important Note Regarding the Makefile

Do not change any of the variables in the Makefile as it may cause the executable to segfault.

### Breakdown of each Makefile command

| Command                    | Action                                                                                                                               |
| -------                    | -----------                                                                                                                          |
| compile                    | Runs the create_folders command. Creates an executable in the output folder. Copies resource folder to the output folder.            |
| run                        | Runs the compile command. Runs the executable in the output folder.                                                                  |
| debug                      | Creates an executable in the output folder with debugging information in the compiled code.                                          |
| valgrind                   | Runs the debug command. Runs a memory checker on the executable in the output folder to see if there is any memory leaks.            |
| delete_lcov                | Delete any \*.gcno, \*.gcda, and \*.info files associated with the lcov command.                                                     |
| copy_and_run_test          | Copies the resource folder to the output folder. Copies and runs the test executable from the test folder to the output folder.      |
| build_test                 | Runs the create_folders and delete_lcov commands. Compiles a test executable with Google Test flags. Runs the copy_and_test command. |
| lcov                       | Runs the build_test command. Creates lcov files on the entire codebase. Then removes the lcov files associated with the lcov folder. |
| genhtml                    | Runs the lcov command. Creates a set of web pages to view the code coverage of the codebase in the genhtml output folder.            |
| coverage                   | Runs the genhtml command. Deletes the test output and lcov output folders.                                                           |
| tidy                       | Runs clang tidy on the code base.                                                                                                    |
| run_doxygen                | Runs the doxygen config file and then deletes the .bak that is created.                                                              |
| docs                       | Runs the run_doxygen command. Uses sphinx to build the docs from the Doxygen XML output.                                                     |
| create_folders             | Creates the boilerplate folders for running other commands. Does not need to be executed individually.                               |
| initialize_repo            | Clones a base C++ project setup and copies it to the current directory.                                                              |

### Input files

This program expects both a SQL dataset file and the text file of its dependencies.

#### SQL Dataset files

- The input .sql files **must** be stored in *resources/sql/*
- These files are expected to follow the following MySQL syntax, where *[\*]* represents an optional value
  - Creating tables

    ```sql
    CREATE TABLE [IF NOT EXISTS] table_name (
        row_name row_definition,
        ...
    );

    ```

  - Defining the row

    ```sql
      data_type [NOT NULL | NULL]
    ```

  - Data types

    ```sql
      VARCHAR(data_size) | INT[(data_size)] | INTEGER[(data_size)]
    ```

#### Functional Dependency files

- The input .txt files **must** be stored in *resources/dependencies/*
- All row names should be row names in the actual SQL dataset file
- These files are expected to follow the following syntax
  - Defining both single and multiple dependencies

    ```txt
      row_name -> row_name | (row_name_one, row_name_two)
    ```

  - Defining both single and multiple multi-valued dependencies

    ```txt
      row_name ->> row_name | (row_name_one, row_name_two)
    ```

  - Defining the primary key of the table

    ```txt
      KEY: row_name | (row_name_one, row_name_two)
    ```

### Specific Examples of Setting a Desired Normal Form

#### Lacking a Primary Key or Nullable (1NF)

- If the functional dependency file lacks a *KEY: ...* declaration, i.e.,

    ```txt
        row_name -> row_name_one
    ```

    then the table is not in 1NF.

- If the SQL dataset file specifies *NULL* in the row_defintion, i.e.,

    ```sql
        CREATE TABLE IF NOT EXISTS table_name (
            row_name INT NULL,
            ...
        );
    ```

    then the table is not in 1NF.

For the purposes of all dependencies to follow, the following table will be used as references.

```sql
    CREATE TABLE IF NOT EXISTS SUPPLY (
        Sname VARCHAR(255) NOT NULL,
        Part_name VARCHAR(255) NOT NULL,
        Proj_name VARCHAR(255) NOT NULL
    );
```

#### Partial Dependencies (2NF)

Below is how to set up a partial dependency as Proj_name depends on only Sname and not the full primary key.

```txt
    KEY: (Sname, Part_name)
    Sname -> Proj_name
```

#### Transitive Dependencies (3NF)

Below is how to set up a transitive dependency as Part_name depends on Sname, the primary key, but Proj_name depends on Part_name

```txt
    KEY: Sname
    Sname -> Part_name
    Part_name -> Proj_name
```

#### BCNF Dependencies (BCNF)

Below is how to set up a BCNF dependency as Proj_name depends on Part_name, but Part_name also depends on Prof_name

```txt
    Key: (Sname, Part_name)
    Sname -> Proj_name
    Part_name -> Proj_name
    Proj_name -> Part_name
```

#### Multi-Valued Dependencies (4NF)

Below is how to set up a multi-valued dependency as both Part_name and Proj_name depend on Sname, but they are all the primary key

```txt
    KEY: (Sname, Part_name, Proj_name)
    Sname ->> (Part_name, Proj_name)
```

#### Join Dependencies (5NF)

Below is how to set up a join dependency as both Part_name and Proj_name depend on Sname, but Proj_name also depends on Part_name

```txt
    KEY: (Sname, Part_name, Proj_name)
    Sname -> (Part_name, Proj_name)
    Part_name -> Proj_name
```

### Determining the Command to Run

- For running the code
  - When prompted for the SQL dataset file, just enter the entire filename
    - i.e. dataset.sql
  - When prompted for the functional dependencies file, just enter the entire filename
    - i.e. dependencies.txt

```bash
    make run
```

- For running the test suite
  - The code base is not fully tested due to a lack of time, but tests are currently on the backburner to make sure the code is bulletproof.

```bash
    make coverage
```

- For checking memory leaks
  - There should be no memory leaks unless the user inputs invalid filenames, but that is currently on the backburner.

```bash
    make valgrind
```

- For creating the documentation
  - The docs are stored in the docs/sphinx/ directory
  - They are currently on the backburner, but the README should suffice for now

```bash
    make docs
```

- For checking linting
  - The code does not fully comply with the .clang-tidy configuration file, but it is currently being worked on

```bash
    make tidy
```
