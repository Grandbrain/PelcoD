/// \file PelcoDEDeviceUDP.hpp
/// \brief Contains classes and functions declarations that provide Pelco-DE UDP
/// device implementation.
/// \bug No known bugs.

#ifndef PELCODE_DEVICE_UDP_HPP
#define PELCODE_DEVICE_UDP_HPP

#include "AbstractPelcoDDevice.hpp"

#include <boost/asio.hpp>

/// Contains classes and functions that provide Pelco-D protocol implementation.
namespace PelcoD {

	/// Class that provides UDP Pelco-DE device implementation.
	class SHARED_API PelcoDEDeviceUDP : public AbstractPelcoDDevice {
	public:

		/// Constructor.
		/// \param[in]	ip
		/// \param[in]	port
		/// \param[in]	max_pan_degrees
		/// \param[in]	max_tilt_degrees
		PelcoDEDeviceUDP(const std::string& ip,
		                 std::uint16_t port,
		                 std::uint16_t maxPanDegrees = 360,
		                 std::uint16_t maxTiltDegrees = 135);

		/// Destructor.
		~PelcoDEDeviceUDP() override;

	public:

		/// Gets pan degrees.
		/// \return Pan degrees.
		std::uint16_t getPanDegrees() const override;

		/// Sets pan degrees.
		/// \param[in]	degrees	Pan degrees.
		void setPanDegrees(std::uint16_t degrees) override;

		/// Gets tilt degrees.
		/// \return Tilt degrees.
		std::uint16_t getTiltDegrees() const override;

		/// Sets tilt degrees.
		/// \param[in]	degrees	Tilt degrees.
		void setTiltDegrees(std::uint16_t degrees) override;

		/// Gets pan steps.
		/// \return Pan steps.
		std::uint16_t getPanSteps() const override;

		/// Gets pan maximum number of steps.
		/// \return Pan maximum number of steps.
		std::uint16_t getPanMaxSteps() const override;

		/// Sets pan steps.
		/// \param[in]	steps	Pan steps.
		void setPanSteps(std::uint16_t steps) override;

		/// Gets tilt steps.
		/// \return Tilt steps.
		std::uint16_t getTiltSteps() const override;

		/// Gets tilt maximum number of steps.
		/// \return Tilt maximum number of steps.
		std::uint16_t getTiltMaxSteps() const override;

		/// Sets tilt steps.
		/// \param[in]	steps	Tilt steps.
		void setTiltSteps(std::uint16_t steps) override;

		/// Gets device temperature.
		/// \return Device temperature.
		std::int16_t getTemperature() const override;

		/// Gets device voltage.
		/// \return Device voltage.
		double getVoltage() const override;

	private:

		/// Number of pan steps per degree of rotation.
		std::uint16_t panStepsPerDegree_;

		/// Number of tilt steps per degree of rotation.
		std::uint16_t tiltStepsPerDegree_;

		/// I/O context.
		boost::asio::io_context context_;

		/// UDP endpoint.
		boost::asio::ip::udp::endpoint endpoint_;

		/// UDP resolver.
		boost::asio::ip::udp::resolver resolver_;

		/// UDP socket.
		mutable boost::asio::ip::udp::socket socket_;
	};
}

#endif
