import test2
import test3
import sys

cobra = 1

def main():
    global cobra
    cobra = cobra + 1
    print("cobra=" + str(cobra))
    test2.increment()
    print("bombolino=" + str(test2.bombolino) + " chornake=" + str(test3.chornake))

