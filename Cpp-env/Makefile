BUILD_DIR := build

all: build viz 

build:
	mkdir -p $(BUILD_DIR)

viz: $(BUILD_DIR)/viz

libraries: .fdm/main.cpp ./fdm/lib/Aerodata/AerodataF18.cpp
	$(CXX) .fdm/main.cpp ./fdm/lib/Aerodata/AerodataF18.cpp -o $(BUILD_DIR)/fdm

$(BUILD_DIR)/viz: build ./fg/main.cpp ./fg/UDPConnect.cpp
	$(CXX) ./fg/main.cpp ./fg/UDPConnect.cpp -o $(BUILD_DIR)/viz

clean:
	rm -rf $(BUILD_DIR)