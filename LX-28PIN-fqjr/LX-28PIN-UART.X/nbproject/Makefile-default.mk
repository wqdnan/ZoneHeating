#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LX-28PIN-UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/LX-28PIN-UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../LX-28PIN-UART.c ../modbus/TIM.c ../modbus/MODBUS.c ../modbus/UART.c ../hardware/EEPROM.c ../hardware/ADC.c ../hardware/IIC.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o ${OBJECTDIR}/_ext/984464531/TIM.o ${OBJECTDIR}/_ext/984464531/MODBUS.o ${OBJECTDIR}/_ext/984464531/UART.o ${OBJECTDIR}/_ext/439174825/EEPROM.o ${OBJECTDIR}/_ext/439174825/ADC.o ${OBJECTDIR}/_ext/439174825/IIC.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o.d ${OBJECTDIR}/_ext/984464531/TIM.o.d ${OBJECTDIR}/_ext/984464531/MODBUS.o.d ${OBJECTDIR}/_ext/984464531/UART.o.d ${OBJECTDIR}/_ext/439174825/EEPROM.o.d ${OBJECTDIR}/_ext/439174825/ADC.o.d ${OBJECTDIR}/_ext/439174825/IIC.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o ${OBJECTDIR}/_ext/984464531/TIM.o ${OBJECTDIR}/_ext/984464531/MODBUS.o ${OBJECTDIR}/_ext/984464531/UART.o ${OBJECTDIR}/_ext/439174825/EEPROM.o ${OBJECTDIR}/_ext/439174825/ADC.o ${OBJECTDIR}/_ext/439174825/IIC.o

# Source Files
SOURCEFILES=../LX-28PIN-UART.c ../modbus/TIM.c ../modbus/MODBUS.c ../modbus/UART.c ../hardware/EEPROM.c ../hardware/ADC.c ../hardware/IIC.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/LX-28PIN-UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F26K80
MP_PROCESSOR_OPTION_LD=18f26k80
MP_LINKER_DEBUG_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o: ../LX-28PIN-UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o   ../LX-28PIN-UART.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/984464531/TIM.o: ../modbus/TIM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/984464531" 
	@${RM} ${OBJECTDIR}/_ext/984464531/TIM.o.d 
	@${RM} ${OBJECTDIR}/_ext/984464531/TIM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/984464531/TIM.o   ../modbus/TIM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/984464531/TIM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/984464531/TIM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/984464531/MODBUS.o: ../modbus/MODBUS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/984464531" 
	@${RM} ${OBJECTDIR}/_ext/984464531/MODBUS.o.d 
	@${RM} ${OBJECTDIR}/_ext/984464531/MODBUS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/984464531/MODBUS.o   ../modbus/MODBUS.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/984464531/MODBUS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/984464531/MODBUS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/984464531/UART.o: ../modbus/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/984464531" 
	@${RM} ${OBJECTDIR}/_ext/984464531/UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/984464531/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/984464531/UART.o   ../modbus/UART.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/984464531/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/984464531/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/439174825/EEPROM.o: ../hardware/EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/439174825" 
	@${RM} ${OBJECTDIR}/_ext/439174825/EEPROM.o.d 
	@${RM} ${OBJECTDIR}/_ext/439174825/EEPROM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/439174825/EEPROM.o   ../hardware/EEPROM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/439174825/EEPROM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/439174825/EEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/439174825/ADC.o: ../hardware/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/439174825" 
	@${RM} ${OBJECTDIR}/_ext/439174825/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/439174825/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/439174825/ADC.o   ../hardware/ADC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/439174825/ADC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/439174825/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/439174825/IIC.o: ../hardware/IIC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/439174825" 
	@${RM} ${OBJECTDIR}/_ext/439174825/IIC.o.d 
	@${RM} ${OBJECTDIR}/_ext/439174825/IIC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/439174825/IIC.o   ../hardware/IIC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/439174825/IIC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/439174825/IIC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o: ../LX-28PIN-UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o   ../LX-28PIN-UART.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/LX-28PIN-UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/984464531/TIM.o: ../modbus/TIM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/984464531" 
	@${RM} ${OBJECTDIR}/_ext/984464531/TIM.o.d 
	@${RM} ${OBJECTDIR}/_ext/984464531/TIM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/984464531/TIM.o   ../modbus/TIM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/984464531/TIM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/984464531/TIM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/984464531/MODBUS.o: ../modbus/MODBUS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/984464531" 
	@${RM} ${OBJECTDIR}/_ext/984464531/MODBUS.o.d 
	@${RM} ${OBJECTDIR}/_ext/984464531/MODBUS.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/984464531/MODBUS.o   ../modbus/MODBUS.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/984464531/MODBUS.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/984464531/MODBUS.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/984464531/UART.o: ../modbus/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/984464531" 
	@${RM} ${OBJECTDIR}/_ext/984464531/UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/984464531/UART.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/984464531/UART.o   ../modbus/UART.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/984464531/UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/984464531/UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/439174825/EEPROM.o: ../hardware/EEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/439174825" 
	@${RM} ${OBJECTDIR}/_ext/439174825/EEPROM.o.d 
	@${RM} ${OBJECTDIR}/_ext/439174825/EEPROM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/439174825/EEPROM.o   ../hardware/EEPROM.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/439174825/EEPROM.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/439174825/EEPROM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/439174825/ADC.o: ../hardware/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/439174825" 
	@${RM} ${OBJECTDIR}/_ext/439174825/ADC.o.d 
	@${RM} ${OBJECTDIR}/_ext/439174825/ADC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/439174825/ADC.o   ../hardware/ADC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/439174825/ADC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/439174825/ADC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/439174825/IIC.o: ../hardware/IIC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/439174825" 
	@${RM} ${OBJECTDIR}/_ext/439174825/IIC.o.d 
	@${RM} ${OBJECTDIR}/_ext/439174825/IIC.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/_ext/439174825/IIC.o   ../hardware/IIC.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/439174825/IIC.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/439174825/IIC.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/LX-28PIN-UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/LX-28PIN-UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/LX-28PIN-UART.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/LX-28PIN-UART.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
