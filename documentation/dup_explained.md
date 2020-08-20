



0 stdin
1 stdout
2 stderror
3 ...
4 ...


# Willen niet meer lezen van stdin maar van file:
1. Bewaard stdin voor later:
    savestdin = dup(0)

dup takes what is in fd[0] (stdin van terminal) en dupliceert het naar de laagste vrije fd

0 stdin
1 stdout
2 stderror
3 savestdin
4 ...

2. Nu kunnen we slot 0 vullen met onze eigen file.

0 our file
1 stdout
2 stderror
3 savestdin
4 ...

Aangezien het systeem altijd leest van stdin, slot 0. Leest het nu van our file als stdin ipv stdin van de terminal.


# Stel we hebben stdin weer nodig (restore)

    dup2(savestdin, 0)

dup2 neemt wat is in savestdin en kopieert dit naar slot 0.
In ons geval savestdin, bevat stdin van de terminal. 

0 stdin
1 stdout
2 stderror
3 savestdin
4 ...