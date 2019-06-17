# A Simple Sat Solver (SSS)

Given a formula, the **Boolean satisfiability problem (SAT)** is to check whether it is satisfiable or not. 
In other words, assigning consistently a value to each variable  (*TRUE* or *FALSE*) in such a way that the 
formula evaluates to *TRUE*.

**SAT** is one of the first problems that was proven to be **NP-complete** and 
there is no known algorithm that efficiently solves each **SAT** problem. It is generally believed that no 
such algorithm exists.

Many real world problems can be codified as a **SAT** formula so **Sat solvers** are becoming more and more 
popular these days. Looking forward to learn more about the topic I decided to implement a Simple Sat Solver (SSS) 
using the DPLL algorithm. I got some inspiration/ideas from many papers, here a list of the most relevants:

- [Heuristic average-case analysis of the backtrack resolution of random 3-Satisfiability instances](https://arxiv.org/pdf/cs/0401011.pdf)
- [A Decision Procedure for Separation Logic in SMT](https://arxiv.org/pdf/1603.06844.pdf)
- [Improving DPLL Solver Performance with Domain-Specific Heuristics: the ASP Case](https://arxiv.org/pdf/1102.2125.pdf)


## Examples

Simple Sat Solver can be used as a command line tool. After compiling and installing the software the command `sss` 
is going to read a file in cnf format and print if the problem is satisfatible or not. 

There are some example in the random3SAT folder with a distinct number of variables (from 100 to 300).

```bash
    sss < random3SAT/vars-200-1.cnf
    SATISFIABLE 346 8986 328
```

The output contains the number of *decisions*, *propagations* and *backtracks* that sss did.

## Quick start

First, you must download the SimpleSatSolver code from our [Git repository](https://github.com/jomsdev/SimpleSatSolver).

To clone the project from Git, `cd` to a suitable location and run
```
git clone https://github.com/jomsdev/SimpleSatSolver.git
```

This will clone the entire contents of the repository. You can check out to the current development branch
if you want to use the last stable version.

To update the project from within the project's folder, you can run the following command:
```
git pull
```

Once you have downloaded the source code, you can `cd` into the source code directory and build and install sss with
```
mkdir build
cd build
cmake ..
make
# it install the files under /usr/local
make install
```


## Future Work

This is an open ended project. There is not hard deadline but I have some ideas I would like to implement:

- **Distributed SatSolver**: Almost all the SatSolvers do not implement a distributed version of the algorithms. Given the size/complexity of some inputs would be really interesting implement some solutions using MPI. 

- **Newer algorithms**: There are hundreds of ideas/modifications trying to speed up sat solvers. It is a hot topic in research so implement some cut-edge algorithms would be great.

## Issue tracker

Found a problem? Want a new feature? First of all see if your issue or idea has [already been reported](../../issues).
If it hasn't, just open a [new clear and descriptive issue](../../issues/new).


## License

Simple Sat Solver (SSS) is under the MIT license. See the [LICENSE](https://github.com/jomsdev/SimpleSatSolver/blob/master/LICENSE) file for details.
