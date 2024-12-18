class Node:
    def __init__(self,name,output):
        self.next = []
        self.name = name
        self.output = output

    def connect(self, other, transition):
        print(f"Adding state: {other.name} on transition: {transition} from state: {self.name}")
        self.next.append((other,transition))

    def drive(self,stateInput):
        print(f"Driving state: {self.name} with input: {stateInput}")
        return self.transition(stateInput)

    def transition(self, state_input):
        for state in self.next:
            nextState = state[0]
            input = state[1]


            if(state_input == input):
                print(f"The next state value is: {nextState.name}")
                return nextState



class FSM:
    def __init__(self, states):
        self.states = states
        self.currentState = states[0]

        print("FSM created:")
        for state in states:
            print(state.name)



    def drive(self, inputs):
        inputs = list(inputs)

        print(inputs)

        for input in inputs:
            print(f"Currently Processing input: {input}")
            print(f"Current state: {self.currentState.name}")

            self.currentState = self.currentState.drive(int(input))

