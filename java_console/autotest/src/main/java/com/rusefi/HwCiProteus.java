package com.rusefi;

import com.rusefi.common.MiscTest;
import com.rusefi.f4discovery.CompositeLoggerTest;
import com.rusefi.f4discovery.HighRevTest;
import com.rusefi.proteus.ProteusAnalogTest;

public class HwCiProteus {
    public static void main(String[] args) {
        CmdJUnitRunner.runHardwareTestAndExit(new Class[]{
                CompositeLoggerTest.class,
                HighRevTest.class,
                MiscTest.class,
                ProteusAnalogTest.class,
        });
    }
}
