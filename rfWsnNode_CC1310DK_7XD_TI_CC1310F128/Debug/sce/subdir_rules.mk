################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
sce/scif.obj: ../sce/scif.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="C:/Users/antsis/workspace_v6_1/rfWsnNode_CC1310DK_7XD_TI_CC1310F128" --include_path="C:/Users/antsis/workspace_v6_1/rfWsnNode_CC1310DK_7XD_TI_CC1310F128/easylink" --include_path="C:/Users/antsis/workspace_v6_1/rfWsnNode_CC1310DK_7XD_TI_CC1310F128/smartrf_settings" --include_path="C:/Users/antsis/workspace_v6_1/rfWsnNode_CC1310DK_7XD_TI_CC1310F128/sce" --include_path="C:/ti/tirtos_cc13xx_cc26xx_2_16_00_08/products/cc13xxware_2_03_01_16780" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/include" -g --define=DEBUG --define=ccs --diag_wrap=off --display_error_number --diag_warning=225 --diag_warning=255 --gen_func_subsections=on --preproc_with_compile --preproc_dependency="sce/scif.pp" --obj_directory="sce" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sce/scif_framework.obj: ../sce/scif_framework.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="C:/Users/antsis/workspace_v6_1/rfWsnNode_CC1310DK_7XD_TI_CC1310F128" --include_path="C:/Users/antsis/workspace_v6_1/rfWsnNode_CC1310DK_7XD_TI_CC1310F128/easylink" --include_path="C:/Users/antsis/workspace_v6_1/rfWsnNode_CC1310DK_7XD_TI_CC1310F128/smartrf_settings" --include_path="C:/Users/antsis/workspace_v6_1/rfWsnNode_CC1310DK_7XD_TI_CC1310F128/sce" --include_path="C:/ti/tirtos_cc13xx_cc26xx_2_16_00_08/products/cc13xxware_2_03_01_16780" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/include" -g --define=DEBUG --define=ccs --diag_wrap=off --display_error_number --diag_warning=225 --diag_warning=255 --gen_func_subsections=on --preproc_with_compile --preproc_dependency="sce/scif_framework.pp" --obj_directory="sce" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sce/scif_osal_tirtos.obj: ../sce/scif_osal_tirtos.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib --abi=eabi -me --include_path="C:/Users/antsis/workspace_v6_1/rfWsnNode_CC1310DK_7XD_TI_CC1310F128" --include_path="C:/Users/antsis/workspace_v6_1/rfWsnNode_CC1310DK_7XD_TI_CC1310F128/easylink" --include_path="C:/Users/antsis/workspace_v6_1/rfWsnNode_CC1310DK_7XD_TI_CC1310F128/smartrf_settings" --include_path="C:/Users/antsis/workspace_v6_1/rfWsnNode_CC1310DK_7XD_TI_CC1310F128/sce" --include_path="C:/ti/tirtos_cc13xx_cc26xx_2_16_00_08/products/cc13xxware_2_03_01_16780" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/include" -g --define=DEBUG --define=ccs --diag_wrap=off --display_error_number --diag_warning=225 --diag_warning=255 --gen_func_subsections=on --preproc_with_compile --preproc_dependency="sce/scif_osal_tirtos.pp" --obj_directory="sce" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


