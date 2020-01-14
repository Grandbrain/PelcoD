/// \file AbstractPelcoDDevice.hpp
/// \brief Contains classes and functions declarations that provide abstract
/// Pelco-D device implementation.
/// \bug No known bugs.

#ifndef ABSTRACT_PELCOD_DEVICE_HPP
#define ABSTRACT_PELCOD_DEVICE_HPP

#include "Export.hpp"

#include <cstdint>
#include <stdexcept>

/// Contains classes and functions that provide Pelco-D protocol implementation.
namespace PelcoD {

	/// Class that provides abstract Pelco-D device implementation.
	class SHARED_API AbstractPelcoDDevice {
	public:

		/// Destructor.
		virtual ~AbstractPelcoDDevice() = 0;

	public:

		/// Gets pan degrees.
		/// \return Pan degrees.
		/// \throw std::logic_error by default.
		virtual std::uint16_t getPanDegrees() const;

		/// Sets pan degrees.
		/// \param[in]	degrees	Pan degrees.
		/// \throw std::logic_error by default.
		virtual void setPanDegrees(std::uint16_t degrees);

		/// Gets tilt degrees.
		/// \return Tilt degrees.
		/// \throw std::logic_error by default.
		virtual std::uint16_t getTiltDegrees() const;

		/// Sets tilt degrees.
		/// \param[in]	degrees	Tilt degrees.
		/// \throw std::logic_error by default.
		virtual void setTiltDegrees(std::uint16_t degrees);

		/// Gets pan steps.
		/// \return Pan steps.
		/// \throw std::logic_error by default.
		virtual std::uint16_t getPanSteps() const;

		/// Gets pan maximum number of steps.
		/// \return Pan maximum number of steps.
		/// \throw std::logic_error by default.
		virtual std::uint16_t getPanMaxSteps() const;

		/// Sets pan steps.
		/// \param[in]	steps	Pan steps.
		/// \throw std::logic_error by default.
		virtual void setPanSteps(std::uint16_t steps);

		/// Gets tilt steps.
		/// \return Tilt steps.
		/// \throw std::logic_error by default.
		virtual std::uint16_t getTiltSteps() const;

		/// Gets tilt maximum number of steps.
		/// \return Tilt maximum number of steps.
		/// \throw std::logic_error by default.
		virtual std::uint16_t getTiltMaxSteps() const;

		/// Sets tilt steps.
		/// \param[in]	steps	Tilt steps.
		/// \throw std::logic_error by default.
		virtual void setTiltSteps(std::uint16_t steps);

		/// Gets device temperature.
		/// \return Device temperature.
		/// \throw std::logic_error by default.
		virtual std::int16_t getTemperature() const;

		/// Gets device voltage.
		/// \return Device voltage.
		/// \throw std::logic_error by default.
		virtual double getVoltage() const;
	};
}

#endif
