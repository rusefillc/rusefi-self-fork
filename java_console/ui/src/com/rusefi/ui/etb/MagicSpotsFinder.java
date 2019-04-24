package com.rusefi.ui.etb;

import com.rusefi.ETBPane;
import com.rusefi.core.MessagesCentral;
import com.rusefi.core.Sensor;
import com.rusefi.core.SensorCentral;
import com.rusefi.io.CommandQueue;
import com.rusefi.io.InvocationConfirmationListener;
import org.putgemin.VerticalFlowLayout;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;

import static com.rusefi.Timeouts.SECOND;

/**
 * This tool finds interesting ETB duty cycles like the value when in starts to open or the value
 * when it's completely open
 * <p>
 * (c) Andrey Belomutskiy
 * 10/21/2018
 */
public class MagicSpotsFinder {
    private static final long SLEEP = SECOND;
    // how much do we want to change duty cycle on each iteration?
    private static final double DUTY_CYCLE_STEP = 0.5;
    private static final String MAGIC_SPOTS_FINDER = "Magic Spots Finder";
    private static final int INITIAL_SLEEP = 10 * SECOND;
    private final JButton button = new JButton(MAGIC_SPOTS_FINDER);
    private final ScheduledExecutorService executor = Executors.newSingleThreadScheduledExecutor();
    // close to zero but not really zero so that we can validate this value
    private final static double LOW_VALUE = 0.5;
//    private boolean isStarted;


    private State state;
    private double currentValue;
    /**
     * here we record at which duty cycle ETB would start moving
     */
    private double startedToOpenValue;
    private double reached100Value;
    private double startedToCloseValue;
    private double backToZeroValue;

    private final JPanel points = new JPanel(new VerticalFlowLayout());
    private final JLabel startedToOpenValueLabel = new JLabel("n/a");
    private final JLabel reached100ValueLabel = new JLabel("n/a");
    private final JLabel startedToCloseValueLabel = new JLabel("n/a");
    private final JLabel backToZeroValueLabel = new JLabel("n/a");

    private final InvocationConfirmationListener goingDown = new InvocationConfirmationListener() {
        @Override
        public void onCommandConfirmation() {
            state = State.GOING_DOWN;

            executor.execute(new Runnable() {
                @Override
                public void run() {
                    sleep(SLEEP);

                    double tpsPosition = SensorCentral.getInstance().getValue(Sensor.TPS);
                    MessagesCentral.getInstance().postMessage(getClass(), "ETB duty " + currentValue + ": tps=" + tpsPosition);

                    if (tpsPosition >= 100) {
                        currentValue -= DUTY_CYCLE_STEP;
                        CommandQueue.getInstance().write(ETBPane.SET_ETB + currentValue, goingDown);
                    } else if (tpsPosition > 0) {

                        if (startedToCloseValue == 0) {
                            // if that's the first we've moved let's remember duty cycle value
                            startedToCloseValue = currentValue;
                            startedToCloseValueLabel.setText(String.format("Started Close %.1f", startedToCloseValue));
                            MessagesCentral.getInstance().postMessage(getClass(), "Started to close at " + startedToCloseValue);
                        }

                        currentValue -= DUTY_CYCLE_STEP;
                        CommandQueue.getInstance().write(ETBPane.SET_ETB + currentValue, goingDown);
                    } else {
                        backToZeroValue = currentValue;
                        backToZeroValueLabel.setText(String.format("Back Zero %.1f", backToZeroValue));
                        MessagesCentral.getInstance().postMessage(getClass(), "Back closed to close at " + backToZeroValue);

                        MessagesCentral.getInstance().postMessage(getClass(), "startedToOpenValue = " + startedToOpenValue + ", reached100Value = " + reached100Value);
                        MessagesCentral.getInstance().postMessage(getClass(), "startedToCloseValue = " + startedToCloseValue + ", backToZeroValue = " + backToZeroValue);
                        button.setEnabled(true);
                        button.setText(MAGIC_SPOTS_FINDER);
                    }
                }
            });
        }
    };

    private final InvocationConfirmationListener goingUp = new InvocationConfirmationListener() {
        @Override
        public void onCommandConfirmation() {
            state = State.GOING_UP;

            executor.execute(new Runnable() {
                @Override
                public void run() {
                    sleep(SLEEP);

                    double tpsPosition = SensorCentral.getInstance().getValue(Sensor.TPS);
                    MessagesCentral.getInstance().postMessage(getClass(), "ETB duty " + currentValue + ": tps=" + tpsPosition);

                    if (tpsPosition == 0) {
                        // ETB has not moved yet, keep going up
                        currentValue += DUTY_CYCLE_STEP;
                        CommandQueue.getInstance().write(ETBPane.SET_ETB + currentValue, goingUp);
                    } else if (tpsPosition < 100) {

                        if (startedToOpenValue == 0) {
                            // if that's the first we've moved let's remember duty cycle value
                            startedToOpenValue = currentValue;
                            startedToOpenValueLabel.setText(String.format("Start to open: %.1f", startedToOpenValue));
                            MessagesCentral.getInstance().postMessage(getClass(), "Started to open at " + startedToOpenValue);
                        }


                        // ETB has not reached 100%, keep going up
                        currentValue += DUTY_CYCLE_STEP;
                        CommandQueue.getInstance().write(ETBPane.SET_ETB + currentValue, goingUp);

                    } else {
                        // looks like we have reached 100%, cool!
                        reached100Value = currentValue;
                        reached100ValueLabel.setText(String.format("Reached 100: %.1f", reached100Value));
                        MessagesCentral.getInstance().postMessage(getClass(), "startedToOpenValue = " + startedToOpenValue + ", reached100Value = " + reached100Value);

                        currentValue -= DUTY_CYCLE_STEP;
                        CommandQueue.getInstance().write(ETBPane.SET_ETB + currentValue, goingDown);
                    }
                }

            });

        }
    };

    public JPanel getPoints() {
        return points;
    }

    // settings are confirmed, let's start going up from zero
    private InvocationConfirmationListener setDebugModeConfiguration = new InvocationConfirmationListener() {
        @Override
        public void onCommandConfirmation() {
            executor.execute(new Runnable() {
                @Override
                public void run() {
                    state = State.START;

                    MessagesCentral.getInstance().postMessage(getClass(), "Start!");
                    resetValues();

                    CommandQueue.getInstance().write(ETBPane.SET_ETB + currentValue, goingUp);
                    sleep(INITIAL_SLEEP);
                }
            });
        }
    };

    private void resetValues() {
        currentValue = LOW_VALUE;
        startedToOpenValue = 0;
        reached100Value = 0;
        startedToCloseValue = 0;
        backToZeroValue = 0;
    }

    public MagicSpotsFinder() {
        points.add(startedToOpenValueLabel);
        points.add(reached100ValueLabel);
        points.add(startedToCloseValueLabel);
        points.add(backToZeroValueLabel);

        button.addActionListener(new AbstractAction() {
            @Override
            public void actionPerformed(ActionEvent e) {
                button.setEnabled(false);
                button.setText("Running...");
//                if (!isStarted) {
////                    metric.start();
//                    isStarted = true;
//                }
                executor.execute(new Runnable() {
                    @Override
                    public void run() {
                        // magic constant for DBG_ELECTRONIC_THROTTLE_EXTRA
                        state = State.DEBUG_MODE;
                        CommandQueue.getInstance().write("set debug_mode " + 29, setDebugModeConfiguration);
                    }
                });
            }
        });
    }

    public JComponent getButton() {
        return button;
    }

    private void sleep(long millis) {
        try {
            MessagesCentral.getInstance().postMessage(getClass(), "Sleeping " + millis + "ms");
            Thread.sleep(millis);
        } catch (InterruptedException unexpected) {
            unexpected.printStackTrace();
            throw new IllegalStateException(unexpected);
        }
    }

    private enum State {
        /**
         * To begin we need to adjust some settings
         */
        DEBUG_MODE,
        /**
         * Once settings change is confirmed we are here
         */
        START,
        GOING_UP,
        GOING_DOWN,
    }
}
