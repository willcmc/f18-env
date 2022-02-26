BUILD_DIR = build
FDM_EXEC = $(BUILD_DIR)/fdm
VIZ_EXEC = $(BUILD_DIR)/viz

BUILD_DEPENDS = fdm/lib/Aerodata/AerodataF18.cpp fg/visualizer.cpp fg/UDPConnect.cpp

all: build $(FDM_EXEC)

build:
	mkdir -p $(BUILD_DIR)

$(FDM_EXEC): build $(BUILD_DEPENDS)
	$(CXX) fdm/main.cpp $(BUILD_DEPENDS) -o $(FDM_EXEC)

clean:
	rm -rf $(BUILD_DIR)