package com.rusefi.pinout;

import com.rusefi.ReaderStateImpl;
import com.rusefi.newparse.DefinitionsState;
import org.junit.Ignore;
import org.junit.Test;

import java.io.*;

import static com.rusefi.test.ConfigDefinitionTest.FIRMWARE;
import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.assertFalse;

public class PinoutLogicHellen112_17_Test {
    @Test
    @Ignore // this was only useful while figuring out the problem
    public void testRealFiled() throws IOException {
        // a bit nasty, do we have similar anywhere else already?
        FileSystemBoardInputsReaderImpl.PREFIX = FIRMWARE + File.separator;

        ReaderStateImpl state = new ReaderStateImpl();
        state.getEnumsReader().read(new FileReader(FileSystemBoardInputsReaderImpl.PREFIX + "controllers/algo/rusefi_hw_stm32_enums.h"));
        state.getEnumsReader().read(new FileReader(FileSystemBoardInputsReaderImpl.PREFIX + "controllers/algo/rusefi_hw_adc_enums.h"));

        assertFalse(state.getEnumsReader().getEnums().isEmpty());


        DefinitionsState definitionState = state.getEnumsReader().parseState;

        StringWriter boardNamesTestWriter = new StringWriter();

        StringWriter outputsTestWriter = new StringWriter();

        PinoutLogic logic = new PinoutLogic(new FileSystemBoardInputsReaderImpl(FileSystemBoardInputsReaderImpl.PREFIX + "config/boards/hellen/hellen-112-17/") {
            @Override
            public Writer getBoardNamesWriter() {
                return boardNamesTestWriter;
            }

            @Override
            public Writer getOutputsWriter() {
                return outputsTestWriter;
            }
        });

        logic.registerBoardSpecificPinNames(state.getVariableRegistry(), definitionState, state.getEnumsReader());


        assertEquals("//DO NOT EDIT MANUALLY, let automation work hard.\n" +
                "\n" +
                "// auto-generated by PinoutLogic.java based on ..\\..\\firmware\\config\\boards\\hellen\\hellen-112-17\\connectors\\main.yaml\n" +
                "#include \"pch.h\"\n" +
                "\n" +
                "// see comments at declaration in pin_repository.h\n" +
                "const char * getBoardSpecificPinName(brain_pin_e brainPin) {\n" +
                "\tswitch(brainPin) {\n" +
                "\t\tcase Gpio::E12: return \"231 Cam\";\n" +
                "\t\tcase Gpio::E13: return \"232 VSS\";\n" +
                "\t\tcase Gpio::E6: return \"Main Relay\";\n" +
                "\t\tdefault: return nullptr;\n" +
                "\t}\n" +
                "\treturn nullptr;\n" +
                "}\n", boardNamesTestWriter.toString());

    }

}
