from SR_latch import SRLatch


class DLatch(SRLatch):
    def __init__(self):
        super().__init__()
        self.D = None

    def input(self, d):
        self.D = d
        super().input(self.D, not self.D)



def main():

    inputs = ["0", "1", "1", "0", "0", "1"]

    latch = DLatch()

    for input in inputs:
        input = int(input)

        latch.input(input)

        print(f"D = {input}, Q = {latch.evaluate()}")


if __name__ == "__main__":
    main()