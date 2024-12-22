class Adder:
    def __init__(self):
        self.input2 = None
        self.input1 = None

    def set_input1(self,input1):
        self.input1 = input1

    def set_input2(self,input2):
        self.input2 = input2


    def input(self,input1, input2):
        self.input1 = input1
        self.input2 = input2

    def evaluate(self):
        output = self.input1 ^ self.input2
        carryout = self.input1 and self.input2

        return output,carryout

    def print(self):
        print(f"HALF ADDER: Input -> {self.input1} {self.input2}")


class FullAdder:
    def __init__(self):
        self.adder1 = Adder()
        self.adder2 = Adder()
        # print("FULL ADDER INITIALIZED")
        # self.state()

    def state(self):
        print('-----------------')
        print('FULL ADDER STATE:')
        self.adder1.print()
        self.adder2.print()
        print('-----------------')


    def input(self,input):

        inputs = list(input)

        input1 = int(inputs[0])
        input2 = int(inputs[1])
        carryin = int(inputs[2])

        self.adder1.input(input1,input2)
        self.adder2.input(carryin,None)

        # self.state()

    def evaluate(self):
        # print("EVALUATING FIRST ADDER:")
        output_adder1, carryout_adder1 = self.adder1.evaluate()
        # print(f"result: SUM: {output_adder1}, CARRYOUT: {carryout_adder1}")

        self.adder2.set_input2(output_adder1)
        # self.state()
        output_adder2, carryout_adder2 = self.adder2.evaluate()

        sum = output_adder2

        carryout = carryout_adder1 or carryout_adder2

        return sum, carryout

class nFullAdder(FullAdder):
    def __init__(self, id):
        super().__init__()
        self.id = id

    def print(self):
        return f"FullAdder{self.id}"




class nAdder:
    def __init__(self,n):
        self.adders = [nFullAdder(i) for i in range(n)]
        self.length = n
        self.output = None
        self.state()

    def state(self):
        print("RIPPLE ADDER")
        for i in range(self.length):
            if i == 0:
                print(f"{self.adders[i].print()} ->",end="")
            elif i == self.length - 1:
                print(f" {self.adders[i].print()} -> Output: {self.output}")
            else:
                print(f" {self.adders[i].print()} ->",end="")

    def input(self, input1, input2):
        input1 = list(input1)
        input2 = list(input2)


        inputs = []
        for i in range(self.length):

            A = input1[i]
            B = input2[i]
            inputs.append(f"{A}{B}")

        inputs.reverse()

        print(inputs)

        current_cin = 0
        output = []
        for i in range(len(inputs)):
            current_input = f"{inputs[i]}{current_cin}"
            self.adders[i].input(current_input)
            sum, current_cin = self.adders[i].evaluate()
            output.append(sum)

        output.reverse()

        final_sum = ""
        for bit in output:
            final_sum += str(bit)

        return final_sum


def binary2DEC(input):
    number = list(input)
    sum = 0

    length = len(number)

    for i in range(length):
        sum += (2**((length -1) - i))*int(number[i])

    return sum




def main():

    fulladder = nAdder(4)



    print(f"{binary2DEC('0100')} + {binary2DEC('0101')} = {binary2DEC(fulladder.input('0100','0101'))}")





if __name__ == "__main__":
    main()