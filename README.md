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

To install in a Kaggle notebook:

```
!pip install cudagrad
```

Distributed as:

- A source distribution, requiring the `cmake` command, and optionally the `nvcc` command, to be available at installation time.
- A binary distribution, targeting the Kaggle environment:
    - Kaggle Python: [Kaggle notebook](https://www.kaggle.com/code/yrmoore/cudagrad-0-2-8-whl)
    - Kaggle Python with GPU (NVIDIA P100): [Kaggle notebook](https://www.kaggle.com/code/yrmoore/cudagrad-0-2-8-gpu-whl)

# Examples

The following examples were written purely in Python using only [`cudagrad.Tensor`](https://github.com/yrmo/cudagrad/blob/main/Tensor.ipynb) for learning:


### OR


![](https://raw.githubusercontent.com/yrmo/cudagrad/refs/heads/main/benchmarks/_cudagrad/plots/or.jpg)

0.52 seconds (59.5% faster than `torch`)

[`/benchmarks/_cudagrad/or.py`](https://github.com/yrmo/cudagrad/blob/main/benchmarks/_cudagrad/or.py)


### XOR


![](https://raw.githubusercontent.com/yrmo/cudagrad/refs/heads/main/benchmarks/_cudagrad/plots/xor.jpg)

4.5 seconds (39.2% faster than `torch`)

[`/benchmarks/_cudagrad/xor.py`](https://github.com/yrmo/cudagrad/blob/main/benchmarks/_cudagrad/xor.py)


### MOONS


![](https://raw.githubusercontent.com/yrmo/cudagrad/refs/heads/main/benchmarks/_cudagrad/plots/moons.jpg)

14.25 seconds (5.8% slower than `torch`)

[`/benchmarks/_cudagrad/moons.py`](https://github.com/yrmo/cudagrad/blob/main/benchmarks/_cudagrad/moons.py)

