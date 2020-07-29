# Linked List

## Why double pointers are used in linked list?

It is clear that both methods (single pointer and double pointer ) lead to the same result.

**Double-pointers** are used as arguments of a function when the function **modifies head of the linked list (updates the list) without needing to return the head again**

but when using Single-pointers as arguments of function that changes/modifies the head (updates the list) **you must return the head pointer ,else the effect won’t be noticed.**

>Het lijkt echt te gaan om het veranderen van de HEAD niet het aanpassen ergens midden in de lijst. Dus als we lstadd_back aanroepen is er een kans dat de head wordt aangepast. Dus altijd ** dubbel pointer mee geven, vanaf de locatie waar je de geupdate head weer wil kunnen ontvangen:

bijv.

- Functie 1. -distributer
    * functie 1.A.
        #functie 1.A.1.
            In deze functie head aangepast
In hoofd functie 1 willen we ook de geupdate head kunnen ontvangen omdat we deze misschien ook wel meegeven aan functie 1.B 

## Why make a copy of the head pointer

have to make a copy of head otherwise the head is not pointing to the beginning of the list anymore when finished looping through it.