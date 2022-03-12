# F-18 Flight Dynamics and Simulation

- Nonlinear model: AoA from -14° to +90°
- FlightGear integration for visualization

## Usage
Clone the repository using
```
git clone https://github.com/willcmc/f18-env.git
```

Install FlightGear by doing
```
sudo add-apt-repository ppa:saiarcot895/flightgear
sudo apt-get update
sudo apt-get install flightgear
```
Set your `FG_HOME` and `FG_ROOT` environment variables by doing the following
```
export FG_HOME=/home/`whoami`/.fgfs
export FG_ROOT=/usr/share/games/flightgear
```
In case your installation and home directories are different (due to building from source), you must make the appropriate changes.

Install the F-18 Addon (bundled in /Installs) by running the following in the top-level directory
```
cd Installs/
cp -R f-18 $FG_HOME/Aircraft
```

Make sure you are able to run FlightGear as a non-sudo user on the command line by trying `fgfs`.

The cpp codes are linked and built using a Makefile. Build the simulator using `make`.
The main executable (currently) is ./build/fdm, so the main code can be executed using `./build/fdm` while in the top-level folder.

William E. Retnaraj
