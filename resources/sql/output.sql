make create_folders
make[1]: Entering directory '/home/phaysik/git/database-normalizer'
mkdir -p .\/resources
mkdir -p .\/build
make[1]: Leaving directory '/home/phaysik/git/database-normalizer'
g++ -std=c++2a -O3 -pedantic -pedantic-errors -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wswitch-default -Wundef -Wno-unused -Wfloat-equal -Wconversion -Winline -Wzero-as-null-pointer-constant -Wmissing-noreturn -Wunreachable-code -Wvariadic-macros -Wwrite-strings -Wunsafe-loop-optimizations -Werror -Iinclude src/Normalizer/normalizer.cpp src/Interpreter/Lexer/lexer.cpp src/Interpreter/Lexer/lexerValidator.cpp src/Interpreter/Parser/parser.cpp src/Interpreter/Parser/parserValidator.cpp src/Interpreter/Token/token.cpp src/Dependencies/DependencyRow/dependencyRow.cpp src/Dependencies/dependencyManager.cpp src/FileManager/fileManager.cpp src/FileManager/fileValidator.cpp src/Table/TableRow/RowDefinition/genericRowDefinition.cpp src/Table/TableRow/tableRow.cpp src/Table/table.cpp src/Table/ForeignKey/foreignKey.cpp src/main.cpp   -o .\/build/main
cp -r .\/resources .\/build
.\/build/main
Enter the path to the SQL dataset file (It must be in the resources/sql folder): Enter the path to the functional dependencies file (It must be in the resources/dependencies folder): Enter the normalization form required (1: 1NF, 2: 2NF, 3: 3NF, B: BCNF, 4: 4NF, 5: 5NF): CREATE TABLE Part_nameProj_nameTable(
	Part_name VARCHAR(255) NOT NULL,
	Proj_name VARCHAR(255) NOT NULL,
	PRIMARY KEY(Part_name, Proj_name)
);

CREATE TABLE SnameProj_nameTable(
	Sname VARCHAR(255) NOT NULL,
	Proj_name VARCHAR(255) NOT NULL,
	PRIMARY KEY(Sname, Proj_name)
);

CREATE TABLE SnamePart_nameTable(
	Sname VARCHAR(255) NOT NULL,
	Part_name VARCHAR(255) NOT NULL,
	PRIMARY KEY(Sname, Part_name)
);


