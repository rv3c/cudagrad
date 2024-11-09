# type: ignore

from os import environ, system
from pstats import Stats
from textwrap import dedent

README = """\
<div align="center">
<h1>
    <div>cudagrad</div>
</h1>

CUDA C++ strided float tensor automatic differentiation engine with Python bindings

</div>

# Install

Available on [PyPI](https://pypi.org/project/cudagrad/):

```
pip install cudagrad
```

Distributed as:

- A source distribution, requiring the `cmake` command, and optionally the `nvcc` command, to be available at installation time.
- A binary distribution, targeting the [Kaggle Python docker images](https://github.com/Kaggle/docker-python):
    - CPU-only binary: [Kaggle notebook example](https://www.kaggle.com/code/yrmoore/cudagrad-0-2-4-whl)
    - GPU accelerator binary: Work in Progress

# Examples

The following examples were written purely in Python using only [`cudagrad.Tensor`](https://github.com/yrmo/cudagrad/blob/main/Tensor.ipynb) for learning:

"""


def compare(c: float, t: float) -> float:
    if t == 0:
        raise ValueError
    return ((c - t) / t) * 100


def profile(examples: list[str]):
    global README

    for example in examples:
        # system(
        #     f"python -m cProfile -o ./benchmarks/_cudagrad/profiles/{example}.prof ./benchmarks/_cudagrad/{example}.py"
        # )
        # system(
        #     f"python -m cProfile -o ./benchmarks/_torch/profiles/{example}.prof ./benchmarks/_torch/{example}.py"
        # )
        t = Stats(f"./benchmarks/_torch/profiles/{example}.prof")
        c = Stats(f"./benchmarks/_cudagrad/profiles/{example}.prof")
        print(f"{t.total_tt=}")
        print(f"{c.total_tt=}")
        percent = compare(c.total_tt, t.total_tt)
        README = README + dedent(
            f"""\

### {example.upper()}


![](https://raw.githubusercontent.com/yrmo/cudagrad/refs/heads/main/benchmarks/_cudagrad/plots/{example}.jpg)

{round(c.total_tt, 2)} seconds ({abs(percent):.1f}% {"faster" if percent <= 0 else "slower"} than `torch`)

[`/benchmarks/_cudagrad/{example}.py`](https://github.com/yrmo/cudagrad/blob/main/benchmarks/_cudagrad/{example}.py)

"""
        )


if __name__ == "__main__":
    environ["PROFILING"] = "1"
    profile(["or", "xor", "moons"])

    with open("README.md", "w") as f:
        f.write(README)
