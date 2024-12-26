class SRLatch:

    def __init__(self):
        self.input1 = 0
        self.input2 = 0
        self.output = None
        self.evaluate()


    def input(self, input1, input2):
        self.input1 = input1
        self.input2 = input2

    def evaluate(self):
        if self.output is None:
            self.output = 0
        else:
            self.output = int(self.input1 or (not(self.input2) and self.output))

        return self.output




def main():
    latch = SRLatch()

    inputs = ["00","10","01", "10", "10", "01"]

    for input in inputs:
        input = list(input)
        latch.input(int(input[0]), int(input[1]))
        print(f"S = {input[0]}, R = {input[1]}, Q+ = {latch.evaluate()}")

if __name__ == "__main__":
    main()