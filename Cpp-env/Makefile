BUILD_DIR = build
FDM_EXT = $(BUILD_DIR)/fdm
VIZ_EXT = $(BUILD_DIR)/viz

VPATH = fdm/lib/Solver:fdm/lib/Aerodata:fdm/lib/Atmosphere:fdm/lib/Engine:fdm/lib/Equations_of_Motion:fg:fdm:input:fdm/lib/Gauss_Noise_Model

BUILD_DEPENDS  = $(BUILD_DIR)/AerodataF18.o $(BUILD_DIR)/Atmosphere.o
BUILD_DEPENDS += $(BUILD_DIR)/Engine.o $(BUILD_DIR)/Engine_initialize.o 
BUILD_DEPENDS += $(BUILD_DIR)/Engine_data.o $(BUILD_DIR)/rtGetNaN.o
BUILD_DEPENDS += $(BUILD_DIR)/rtGetInf.o $(BUILD_DIR)/rt_nonfinite.o
BUILD_DEPENDS += $(BUILD_DIR)/visualizer.o $(BUILD_DIR)/UDPConnect.o
BUILD_DEPENDS += $(BUILD_DIR)/Equations_of_Motion.o $(BUILD_DIR)/xbox.o
BUILD_DEPENDS += $(BUILD_DIR)/Equations_of_Motion_data.o
BUILD_DEPENDS += $(BUILD_DIR)/Equations_of_Motion_initialize.o
BUILD_DEPENDS += $(BUILD_DIR)/interp1.o $(BUILD_DIR)/solver.o
BUILD_DEPENDS += $(BUILD_DIR)/Gauss_Noise_Model.o

all: build $(FDM_EXT)

build:
	@echo 'Creating build directory.'
	@mkdir -p $(BUILD_DIR)
	
$(BUILD_DIR)/%.o: %.cpp 
	@echo 'Building file: $<'
	@${CXX} -c -o "$@" "$<"

$(FDM_EXT): build $(BUILD_DIR)/main.o $(BUILD_DEPENDS)
	@echo 'Building and linking final files.'
	@$(CXX) $(BUILD_DIR)/main.o $(BUILD_DEPENDS) -o $(FDM_EXT)

check:
	@$(FDM_EXT) -ci
	@echo 'Build check passed.'

clean:
	@rm -rf $(BUILD_DIR)
	@echo 'Cleared build folder.'
