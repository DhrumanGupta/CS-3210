import os
import subprocess
import matplotlib.pyplot as plt
import random
import math


def run_program(n):
    # Run the compiled program with n as an argument and capture the output
    input_str = f"-1\n{n}\n"

    for i in range(n):
        x = random.randint(1, 1000)
        y = random.randint(1, 1000)

        input_str += f"{x} {y}\n"

    result = subprocess.run(
        ["./main.out"], input=input_str, capture_output=True, text=True
    )
    return int(result.stdout.strip())


def main():
    os.system("make")  # Compile the program

    ns = list(range(1, 120_000, 10_000))  # Input sizes
    counters = []
    nlogn = []

    c = 7

    for n in ns:
        count = run_program(n)
        counters.append(count)
        print(f"n = {n}, Counter = {count}")
        nlogn.append(c * n * math.log(n))

    # Plot the results
    plt.figure(figsize=(8, 6))  # Set figure size

    plt.plot(
        ns, counters, marker="o", linestyle="-", label="Actual Operations"
    )  # Keep markers and lines
    plt.plot(
        ns, nlogn, marker="o", linestyle="-", label=f"{c} * n * log(n)"
    )  # Keep markers and lines

    plt.xlabel("Input Size n")
    plt.ylabel(
        "Operations (Counter Value)"
    )  # Labeling it as operations to clarify complexity

    plt.title("Time Complexity: Operations vs Input Size")
    plt.grid(True)
    plt.legend()

    plt.savefig("graph.png")  # Save the plot as a PNG file


if __name__ == "__main__":
    main()
