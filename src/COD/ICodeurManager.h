/*#pragma once

/// @brief Classe abstraite s’occupant de deux codeurs
class ICodeurManager
{
public:
	int getRightTicks();
	int getLeftTicks();

	virtual void readAndReset() = 0;
	virtual void reset() = 0;

// Protégé pour que les classes filles puisse modifier ces valeurs dans readAndReset()
protected:
	int leftTicks = 0, rightTicks = 0;
};
*/
