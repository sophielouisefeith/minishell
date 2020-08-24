


to do

# ctrl D
1. moet niet eruit gaan maar moet in je bash blijven als je typt moet hij niks doen 
getnexline

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




# Meetekenen:

default:
  0 stdin
  1 stdout
  2 stderror
----
Tmpin, tmpout dup en fdin:

  0 stdin
  1 stdout
  2 stderror
**3 tmpin                 (is fd[0] terminal stdin)**
**4 tmpout                (is fd[1] terminal stdout)**
**5 fdin                  (redirection inputfile of terminal stdin fd[0])**

----
While loop, dup2 en close:
**0 "fdin"                (redirection inputfile of terminal stdin fd[0])   //na dup2**
  1 stdout
  2 stderror
  3 tmpin                 (is fd[0] terminal stdin)
  4 tmpout                (is fd[1] terminal stdout)
**5 ...                                                                     //close deletes fdin**

----
ALS in laatste node:
  0 "fdin"                (redirection inputfile of terminal stdin fd[0])
  1 stdout
  2 stderror
  3 tmpin                 (is fd[0] terminal stdin)
  4 tmpout                (is fd[1] terminal stdout)
**5 fdout                 (redirection outputfile of terminal stdout fd[1])**  
----
ALS pipe after:

0 "fdin"                (redirection inputfile of terminal stdin fd[0])
1 stdout
2 stderror
3 tmpin                 (is fd[0] terminal stdin)
4 tmpout                (is fd[1] terminal stdout)
5 ...                   *fdout: gevuld als in laatste node*
**6 fdpipe[0]           read-end pipe**
**7 fdpipe[1]           write-end pipe**
**8 fdin                (fdpipe[0] read-end pipe)**                  
**9 fdout               (fdpipe[1] write-end pipe)**

Nu kunnen we in child ipv naar stdout naar write-end(fdpipe[1]) of pipe schrijven.
In parent proces kunnen we van read-end(fdpipe[0]) of pipe lezen, ipv stdin.
------
Dup2 en close fdout:
  0 "fdin"                (redirection inputfile of terminal stdin fd[0])
**1 "fdout"               (redirection outputfile of terminal stdout fd[1])** //ALS LAATSTE NODE
                          **(fdpipe[1] write-end pipe)**                      //ALS PIPE AFTER
                          **leeg** ???                                        //ALS ;  
  2 stderror
  3 tmpin                 (is fd[0] terminal stdin)
  4 tmpout                (is fd[1] terminal stdout)
**5 ...                   *fdout: gevuld als in laatste node**                 //closed
  6 ...                   *fdpipe[0]: gevuld als pipe after*
  7 ...                   *fdpipe[1]: gevuld als pipe after*
  8 ...                   *fdin: gevuld als pipe after*    
 **9 ...                   *fdout: gevuld als pipe after***                    //closed

----

Alles wordt geforked:
output child komt dus terecht in outputfile/write-end pipe/terminal stdout of leeeeeg???

& repeat while loop!
----
Recover, na while:

**0 "tmpin"             (Recovered: is fd[0] terminal stdin)**
**1 "tmpout"            (Recovered:is fd[1] terminal stdout)**
  2 stderror
**3 ...**                                                         //closed
**4 ...**                                                         //closed

THE END


