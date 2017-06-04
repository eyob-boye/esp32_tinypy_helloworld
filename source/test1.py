import test2
import test3
import sys

cobra = 1

def main():
    global cobra
    cobra = cobra + 1
    print("test1: " + "cobra=" + str(cobra))
    test2.increment()
    print("test1: " + "test2.bombolino=" + str(test2.bombolino) + " test3.chornake=" + str(test3.chornake))

