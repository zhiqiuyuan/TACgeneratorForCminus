lecture project, just write overnight, haven’t fully debugged yet

# usage

under project dir:

## build

```shell
make
```

## run

```shell
./main <input_filename>
```

for example:

```shell
./main ./test/1.cminus
```

# input and output

## input

> input from given file: cminus grammatical code

cminus grammer

![](.\fig\cminus_grammer.jpg)

## output

> output to stdout: corresponding three address code for input code

three address code 

[Slides13.pdf (stanford.edu)](https://web.stanford.edu/class/archive/cs/cs143/cs143.1128/lectures/13/Slides13.pdf)

# drawback

- array not supported yet
- in function_declaration: “BeginFunc N” N is fixed as string now
- after function_call: “PopParmams N” N is fixed as string now

- have only tested on 6 cases under ./test