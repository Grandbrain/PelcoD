/// \file AbstractPelcoDDevice.cpp
/// \brief Contains classes and functions definitions that provide abstract
/// Pelco-D device implementation.
/// \bug No known bugs.

#include "AbstractPelcoDDevice.hpp"

/// Contains classes and functions that provide Pelco-D protocol implementation.
namespace PelcoD {

	/// Destructor.
	/// \details Defaulted default destructor.
	AbstractPelcoDDevice::~AbstractPelcoDDevice() = default;

	/// Gets pan degrees.
	/// \details Gets pan value in degrees.
	/// \return Pan degrees.
	/// \throw std::logic_error by default.
	std::uint16_t AbstractPelcoDDevice::getPanDegrees() const {
		throw std::logic_error("The method is not implemented!");
	}

	/// Sets pan degrees.
	/// \details Sets pan value in degrees.
	/// \param[in]	degrees	Pan degrees.
	/// \throw std::logic_error by default.
	void AbstractPelcoDDevice::setPanDegrees(std::uint16_t degrees) {
		throw std::logic_error("The method is not implemented!");
	}

	/// Gets tilt degrees.
	/// \details Gets tilt value in degrees.
	/// \return Tilt degrees.
	/// \throw std::logic_error by default.
	std::uint16_t AbstractPelcoDDevice::getTiltDegrees() const {
		throw std::logic_error("The method is not implemented!");
	}

	/// Sets tilt degrees.
	/// \details Sets tilt value in degrees.
	/// \param[in]	degrees	Tilt degrees.
	/// \throw std::logic_error by default.
	void AbstractPelcoDDevice::setTiltDegrees(std::uint16_t degrees) {
		throw std::logic_error("The method is not implemented!");
	}

	/// Gets pan steps.
	/// \details Gets pan value in steps.
	/// \return Pan steps.
	/// \throw std::logic_error by default.
	std::uint16_t AbstractPelcoDDevice::getPanSteps() const {
		throw std::logic_error("The method is not implemented!");
	}

	/// Gets pan maximum number of steps.
	/// \details Gets pan maximum value in steps.
	/// \return Pan maximum number of steps.
	/// \throw std::logic_error by default.
	std::uint16_t AbstractPelcoDDevice::getPanMaxSteps() const {
		throw std::logic_error("The method is not implemented!");
	}

	/// Sets pan steps.
	/// \details Sets pan value in steps.
	/// \param[in]	steps	Pan steps.
	/// \throw std::logic_error by default.
	void AbstractPelcoDDevice::setPanSteps(std::uint16_t steps) {
		throw std::logic_error("The method is not implemented!");
	}

	/// Gets tilt steps.
	/// \details Gets tilt value in steps.
	/// \return Tilt steps.
	/// \throw std::logic_error by default.
	std::uint16_t AbstractPelcoDDevice::getTiltSteps() const {
		throw std::logic_error("The method is not implemented!");
	}

	/// Gets tilt maximum number of steps.
	/// \details Gets tilt maximum value in steps.
	/// \return Tilt maximum number of steps.
	/// \throw std::logic_error by default.
	std::uint16_t AbstractPelcoDDevice::getTiltMaxSteps() const {
		throw std::logic_error("The method is not implemented!");
	}

	/// Sets tilt steps.
	/// \details Sets tilt value in steps.
	/// \param[in]	steps	Tilt steps.
	/// \throw std::logic_error by default.
	void AbstractPelcoDDevice::setTiltSteps(std::uint16_t steps) {
		throw std::logic_error("The method is not implemented!");
	}

	/// Gets device temperature.
	/// \details Gets device temperature value.
	/// \return Device temperature.
	/// \throw std::logic_error by default.
	std::int16_t AbstractPelcoDDevice::getTemperature() const {
		throw std::logic_error("The method is not implemented!");
	}

	/// Gets device voltage.
	/// \details Gets device voltage value.
	/// \return Device voltage.
	/// \throw std::logic_error by default.
	double AbstractPelcoDDevice::getVoltage() const {
		throw std::logic_error("The method is not implemented!");
	}
}
