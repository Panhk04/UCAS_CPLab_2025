# CACT compiler skeleton

## using antlr4 to generate files from grammar file

```bash
java -jar ../deps/antlr-4.13.1-complete.jar -Dlanguage=Cpp Hello.g4 -visitor -no-listener
```

or simply run `grammar/gen.sh` to generate lexer/parser/visitor files.

## compile the cmake project

```bash
mkdir -p build
cd build
cmake ..
make -j
```

## test on samples

run `test.sh` to test on samples in `test` folder.