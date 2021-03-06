/* Copyright 2013 Yurii Litvinov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtCore/QHash>

#include "declSpec.h"

#include "servoMotor.h"
#include "powerMotor.h"
#include "sensor.h"
#include "display.h"
#include "battery.h"
#include "sensor3d.h"
#include "encoder.h"
#include "keys.h"
#include "trikGamepad.h"

namespace trikControl {

class Configurer;
class I2cCommunicator;

/// Class representing TRIK controller board and devices installed on it, also provides access
/// to peripherals like motors and sensors.
class TRIKCONTROL_EXPORT Brick : public QObject
{
	Q_OBJECT

public:
	explicit Brick(QThread &guiThread);
	~Brick();

public slots:
	/// Plays given music file on a speaker (in format accepted by aplay utility).
	void playSound(QString const &soundFileName);

	/// Stops all motors and shuts down all current activity.
	void stop();

	/// Returns reference to motor on a given port.
	ServoMotor *servoMotor(QString const &port);

	/// Returns reference to power motor on a given port.
	PowerMotor *powerMotor(QString const &port);

	/// Returns reference to sensor on a given port.
	Sensor *sensor(QString const &port);

	/// Returns reference to on-board accelerometer.
	Sensor3d *accelerometer();

	/// Returns reference to on-board gyroscope.
	Sensor3d *gyroscope();

	/// Returns reference to encoder on given port.
	Encoder *encoder(QString const &port);

	/// Returns reference to battery.
	Battery *battery();

    Keys *keys();

    TrikGamepad *gamepad();

	/// Waits given amount of time in milliseconds and returns.
	void wait(int const &milliseconds) const;

	/// Returns the number of milliseconds since 1970-01-01T00:00:00 UTC.
	qint64 time() const;

	/// Returns reference to class that provides drawing on display.
	Display *display();

private:
	class SleeperThread : public QThread
	{
	public:
		static void msleep(unsigned long msecs)
		{
			QThread::msleep(msecs);
		}
	};

	Encoder *mEncoder1;
	Encoder *mEncoder2;
	Encoder *mEncoder3;
	Encoder *mEncoder4;

	Sensor3d *mAccelerometer;  // has ownership.
	Sensor3d *mGyroscope;  // has ownership.
    Battery *mBattery;  // Has ownership.
    Keys mKeys;
    TrikGamepad trikGamepad;

	QHash<QString, ServoMotor *> mServoMotors;  // Has ownership.
	QHash<QString, PowerMotor *> mPowerMotors;  // Has ownership.
	QHash<QString, Encoder *> mEncoders;  // Has ownership.
	QHash<QString, Sensor *> mSensors;  // Has ownership.

	Configurer const * const mConfigurer;  // Has ownership.
	I2cCommunicator *mI2cCommunicator;  // Has ownership.
	Display mDisplay;
};

}
