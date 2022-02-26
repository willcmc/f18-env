BUILD_DIR = build
FDM_EXT = $(BUILD_DIR)/fdm
VIZ_EXT = $(BUILD_DIR)/viz

VPATH = fdm/lib/Aerodata:fdm/lib/Atmosphere:fg:fdm

BUILD_DEPENDS = $(BUILD_DIR)/AerodataF18.o $(BUILD_DIR)/Atmosphere.o $(BUILD_DIR)/visualizer.o $(BUILD_DIR)/UDPConnect.o

all: build $(FDM_EXT)

build:
	mkdir -p $(BUILD_DIR)
	
$(BUILD_DIR)/%.o: %.cpp 
	@echo 'Building file: $<'
	@${CXX} -c -o "$@" "$<"

$(FDM_EXT): build $(BUILD_DIR)/main.o $(BUILD_DEPENDS)
	$(CXX) $(BUILD_DIR)/main.o $(BUILD_DEPENDS) -o $(FDM_EXT)

clean:
	rm -rf $(BUILD_DIR)
