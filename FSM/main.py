from state import Node, FSM



def main():

    ## mealy FSM (just a fancy way to say graph i guess)

    ## Node A as it appears in the diagram

    s1 = Node("A",0)

    ## Node B as it appears in the diagram

    s2 = Node("B",0)

    ## Node C as it appears in the diagram

    s3 = Node("C",0)

    ## Node D as it appears in the diagram

    s4 = Node("D", 1)

    s1.connect(s1, 0)
    s1.connect(s2,1)

    s2.connect(s1,0)
    s2.connect(s3,1)


    s3.connect(s1,0)
    s3.connect(s4,1)

    s4.connect(s1,0)
    s4.connect(s4,1)


    states = [s1,s2,s3,s4]

    state_machine = FSM(states)

    state_machine.drive("111100110")

    print("END of instruction cycle:")
    print(f"The current state is: {state_machine.currentState.name}")




if __name__ == "__main__":
    main()