from SR_latch import SRLatch


class ClockedDLatch(SRLatch):
    def __init__(self):
        super().__init__()

    def input(self, d, clk):
        d1 = d and clk

        not_d1 = (not d) and clk

        super().input(d1, not_d1)


class DFlipFlop:
    def __init__(self):
        self.master = ClockedDLatch()
        self.slave = ClockedDLatch()

    def input(self, d, clk):
        self.master.input(d, not clk)

        P = self.master.evaluate()

        self.slave.input(P, clk)


    def evaluate(self):
        return self.slave.evaluate()


def main():
    clk_dlatch = DFlipFlop()

    x   = "1111110000000000"
    clk = "0000111100001111"

    x = list(x)
    clk = list(clk)

    prev_clock = None
    current_output = 0

    for i in range(len(x)):
        # First set inputs
        clk_dlatch.input(int(x[i]), int(clk[i]))

        # Then evaluate once
        new_output = clk_dlatch.evaluate()

        if (int(clk[i]) == 1 and prev_clock == '0'):
            print("POSEDGE CLK: VALUE SHOULD CHANGE")

        print(f"X = {x[i]}, CLK = {clk[i]}, Q = {current_output}, Q+ = {new_output}")

        current_output = new_output
        prev_clock = clk[i]

if __name__ == "__main__":
    main()
