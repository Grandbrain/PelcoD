/// \file PelcoDEDeviceUDP.cpp
/// \brief Contains classes and functions definitions that provide Pelco-DE UDP
/// device implementation.
/// \bug No known bugs.

#include "PelcoDEDeviceUDP.hpp"

/// Contains classes and functions that provide Pelco-D protocol implementation.
namespace PelcoD {

	namespace {

		/// Pelco-DE request command to get pan steps.
		/// \details Request command value to obtain pan value in steps.
		constexpr std::uint8_t COMMAND_REQUEST_GET_PAN_STEPS { 0x51 };

		/// Pelco-DE request command to get tilt steps.
		/// \details Request command value to obtain tilt value in steps.
		constexpr std::uint8_t COMMAND_REQUEST_GET_TILT_STEPS { 0x53 };

		/// Pelco-DE request command to get pan maximum number of steps.
		/// \details Request command value to obtain pan maximum value in steps.
		constexpr std::uint8_t COMMAND_REQUEST_GET_PAN_MAX_STEPS { 0x55 };

		/// Pelco-DE request command to get tilt maximum number of steps.
		/// \details Request command value to obtain tilt maximum value in steps.
		constexpr std::uint8_t COMMAND_REQUEST_GET_TILT_MAX_STEPS { 0x57 };

		/// Pelco-DE responce command to get pan steps.
		/// \details Responce command value to obtain pan value in steps.
		constexpr std::uint8_t COMMAND_RESPONCE_GET_PAN_STEPS { 0x61 };

		/// Pelco-DE responce command to get tilt steps.
		/// \details Responce command value to obtain tilt value in steps.
		constexpr std::uint8_t COMMAND_RESPONCE_GET_TILT_STEPS { 0x63 };

		/// Pelco-DE responce command to get pan maximum number of steps.
		/// \details Responce command value to obtain pan maximum value in steps.
		constexpr std::uint8_t COMMAND_RESPONCE_GET_PAN_MAX_STEPS { 0x65 };

		/// Pelco-DE responce command to get tilt maximum number of steps.
		/// \details Responce command value to obtain tilt maximum value in steps.
		constexpr std::uint8_t COMMAND_RESPONCE_GET_TILT_MAX_STEPS { 0x67 };

		/// Pelco-DE request command to set pan steps.
		/// \details Request command value to set pan value in steps.
		constexpr std::uint8_t COMMAND_REQUEST_SET_PAN_STEPS { 0x71 };

		/// Pelco-DE request command to set tilt steps.
		/// \details Request command value to set tilt value in steps.
		constexpr std::uint8_t COMMAND_REQUEST_SET_TILT_STEPS { 0x73 };

		/// Pelco-DE responce command to set pan steps.
		/// \details Responce command value to set pan value in steps.
		constexpr std::uint8_t COMMAND_RESPONCE_SET_PAN_STEPS { 0x7C };

		/// Pelco-DE responce command to set tilt steps.
		/// \details Responce command value to set tilt value in steps.
		constexpr std::uint8_t COMMAND_RESPONCE_SET_TILT_STEPS { 0x7C };

		/// Pelco-DE request command to get temperature.
		/// \details Request command value to obtain temperature value.
		constexpr std::uint8_t COMMAND_REQUEST_GET_TEMPERATURE { 0x91 };

		/// Pelco-DE request command to get voltage.
		/// \details Request command value to obtain voltage value.
		constexpr std::uint8_t COMMAND_REQUEST_GET_VOLTAGE { 0x9B };

		/// Pelco-DE responce command to get temperature.
		/// \details Responce command value to obtain temperature value.
		constexpr std::uint8_t COMMAND_RESPONCE_GET_TEMPERATURE { 0xA1 };

		/// Pelco-DE responce command to get voltage.
		/// \details Responce command value to obtain voltage value.
		constexpr std::uint8_t COMMAND_RESPONCE_GET_VOLTAGE { 0xAB };

		/// Synchronization value.
		/// \details Pelco-DE protocol synchronization value.
		constexpr std::uint8_t SYNCHRONIZATION_VALUE { 0xFF };

		/// Device address.
		/// \details Pelco-DE device logical address.
		constexpr std::uint8_t ADDRESS_VALUE { 0x01 };

		/// Message length.
		/// \details Pelco-DE fixed message length in bytes.
		constexpr std::size_t MESSAGE_LENGTH { 7 };

		/// Device address byte index.
		/// \details The index in the byte array of the message in which the
		/// device logical address is stored.
		constexpr std::size_t ADDRESS_BYTE_INDEX { 1 };

		/// First command byte index.
		/// \details The index in the byte array of the message in which the
		/// first command is stored.
		constexpr std::size_t COMMAND1_BYTE_INDEX { 2 };

		/// Second command byte index.
		/// \details The index in the byte array of the message in which the
		/// second command is stored.
		constexpr std::size_t COMMAND2_BYTE_INDEX { 3 };

		/// Value high byte index.
		/// \details The index in the byte array of the message in which the
		/// value high byte is stored.
		constexpr std::size_t VALUE_HIGH_BYTE_INDEX { 4 };

		/// Value low byte index.
		/// \details The index in the byte array of the message in which the
		/// value low byte is stored.
		constexpr std::size_t VALUE_LOW_BYTE_INDEX { 5 };

		/// Checksum byte index.
		/// \details The index in the byte array of the message in which the
		/// checksum is stored.
		constexpr std::size_t CHECKSUM_BYTE_INDEX { 6 };

		/// Calculates the checksum of a Pelco-DE message.
		/// \details Calculates the sum of all fields in a Pelco-DE message.
		/// \param[in]	message	Pelco-DE message.
		void calculateChecksum(std::array<std::uint8_t,
		                                  MESSAGE_LENGTH>& message) noexcept {

			message[CHECKSUM_BYTE_INDEX] = (
				message[ADDRESS_BYTE_INDEX] +
					message[COMMAND1_BYTE_INDEX] +
					message[COMMAND2_BYTE_INDEX] +
					message[VALUE_HIGH_BYTE_INDEX] +
					message[VALUE_LOW_BYTE_INDEX]) % 0x100;
		}

		/// Creates a Pelco-DE message.
		/// \details Creates a Pelco-DE message based on command and value.
		/// \return Pelco-DE message.
		std::array<std::uint8_t,
		           MESSAGE_LENGTH> createMessage(std::uint8_t command,
		                                         std::uint16_t value = 0) noexcept {

			std::uint8_t valueHighByte = value >> 8u;
			std::uint8_t valueLowByte = value;

			std::array<std::uint8_t, MESSAGE_LENGTH> message = {
				SYNCHRONIZATION_VALUE,
				ADDRESS_VALUE,
				0x00,
				command,
				valueHighByte,
				valueLowByte,
				0x00
			};

			calculateChecksum(message);

			return message;
		}

		/// Sends a Pelco-DE message through a socket.
		/// \details Sends a Pelco-DE message over a UDP socket with the
		/// specified endpoint.
		/// \param[in]	message		Pelco-DE message.
		/// \param[in]	endpoint	Network endpoint.
		/// \param[in]	socket		UDP socket.
		void sendMessage(const std::array<std::uint8_t,
		                                  MESSAGE_LENGTH>& message,
		                 const boost::asio::ip::udp::endpoint& endpoint,
		                 boost::asio::ip::udp::socket& socket) {

			socket.send_to(boost::asio::buffer(message), endpoint);
		}

		/// Receives a Pelco-DE message through a socket.
		/// \details Receives a Pelco-DE message through a UDP socket.
		/// \param[in]	socket	UDP socket.
		/// \return Pelco-DE value.
		std::uint16_t receiveMessage(boost::asio::ip::udp::socket& socket) {
			std::array<std::uint8_t, MESSAGE_LENGTH> message { };
			boost::asio::ip::udp::endpoint endpoint;

			socket.receive_from(boost::asio::buffer(message), endpoint);

			return
				(static_cast<std::uint16_t>(message[VALUE_HIGH_BYTE_INDEX])
					<< 8u) + message[VALUE_LOW_BYTE_INDEX];
		}
	}

	/// Constructor.
	/// \details Initializes object fields.
	/// \param[in]	ip 				IP address.
	/// \param[in]	port 			Port.
	/// \param[in]	maxPanDegrees	Pan maximum number of degrees.
	/// \param[in]	maxTiltDegrees	Tilt maximum number of degrees.
	PelcoDEDeviceUDP::PelcoDEDeviceUDP(const std::string& ip,
	                                   std::uint16_t port,
	                                   std::uint16_t maxPanDegrees,
	                                   std::uint16_t maxTiltDegrees)
		: panStepsPerDegree_(0),
		  tiltStepsPerDegree_(0),
		  socket_(context_),
		  resolver_(context_) {

		endpoint_ = *resolver_.resolve(boost::asio::ip::udp::v4(),
		                               ip, std::to_string(port)).begin();

		socket_.open(boost::asio::ip::udp::v4());

		panStepsPerDegree_ = getPanMaxSteps() / maxPanDegrees;
		tiltStepsPerDegree_ = getTiltMaxSteps() / maxTiltDegrees;
	}

	/// Destructor.
	/// \details Defaulted default destructor.
	PelcoDEDeviceUDP::~PelcoDEDeviceUDP() = default;

	/// Gets pan degrees.
	/// \details Gets pan value in degrees.
	/// \return Pan degrees.
	std::uint16_t PelcoDEDeviceUDP::getPanDegrees() const {
		return getPanSteps() / panStepsPerDegree_;
	}

	/// Sets pan degrees.
	/// \details Sets pan value in degrees.
	/// \param[in]	degrees	Pan degrees.
	void PelcoDEDeviceUDP::setPanDegrees(std::uint16_t degrees) {
		degrees %= 360;
		setPanSteps(degrees * panStepsPerDegree_);
	}

	/// Gets tilt degrees.
	/// \details Gets tilt value in degrees.
	/// \return Tilt degrees.
	std::uint16_t PelcoDEDeviceUDP::getTiltDegrees() const {
		return getTiltSteps() / tiltStepsPerDegree_;
	}

	/// Sets tilt degrees.
	/// \details Sets tilt value in degrees.
	/// \param[in]	degrees	Tilt degrees.
	void PelcoDEDeviceUDP::setTiltDegrees(std::uint16_t degrees) {
		degrees %= 135;
		setTiltSteps(degrees * tiltStepsPerDegree_);
	}

	/// Gets pan steps.
	/// \details Gets pan value in steps.
	/// \return Pan steps.
	std::uint16_t PelcoDEDeviceUDP::getPanSteps() const {
		sendMessage(createMessage(COMMAND_REQUEST_GET_PAN_STEPS),
		            endpoint_, socket_);

		return receiveMessage(socket_);
	}

	/// Gets pan maximum number of steps.
	/// \details Gets pan maximum value in steps.
	/// \return Pan maximum number of steps.
	std::uint16_t PelcoDEDeviceUDP::getPanMaxSteps() const {
		sendMessage(createMessage(COMMAND_REQUEST_GET_PAN_MAX_STEPS),
		            endpoint_, socket_);

		return receiveMessage(socket_);
	}

	/// Sets pan steps.
	/// \details Sets pan value in steps.
	/// \param[in]	steps	Pan steps.
	void PelcoDEDeviceUDP::setPanSteps(std::uint16_t steps) {
		sendMessage(createMessage(COMMAND_REQUEST_SET_PAN_STEPS, steps),
		            endpoint_, socket_);

		receiveMessage(socket_);
	}

	/// Gets tilt steps.
	/// \details Gets tilt value in steps.
	/// \return Tilt steps.
	std::uint16_t PelcoDEDeviceUDP::getTiltSteps() const {
		sendMessage(createMessage(COMMAND_REQUEST_GET_TILT_STEPS),
		            endpoint_, socket_);

		return receiveMessage(socket_);
	}

	/// Gets tilt maximum number of steps.
	/// \details Gets tilt maximum value in steps.
	/// \return Tilt maximum number of steps.
	std::uint16_t PelcoDEDeviceUDP::getTiltMaxSteps() const {
		sendMessage(createMessage(COMMAND_REQUEST_GET_TILT_MAX_STEPS),
		            endpoint_, socket_);

		return receiveMessage(socket_);
	}

	/// Sets tilt steps.
	/// \details Sets tilt value in steps.
	/// \param[in]	steps	Tilt steps.
	void PelcoDEDeviceUDP::setTiltSteps(std::uint16_t steps) {
		sendMessage(createMessage(COMMAND_REQUEST_SET_TILT_STEPS, steps),
		            endpoint_, socket_);

		receiveMessage(socket_);
	}

	/// Gets device temperature.
	/// \details Gets device temperature value.
	/// \return Device temperature.
	std::int16_t PelcoDEDeviceUDP::getTemperature() const {
		sendMessage(createMessage(COMMAND_REQUEST_GET_TEMPERATURE),
		            endpoint_, socket_);

		return receiveMessage(socket_);
	}

	/// Gets device voltage.
	/// \details Gets device voltage value.
	/// \return Device voltage.
	double PelcoDEDeviceUDP::getVoltage() const {
		sendMessage(createMessage(COMMAND_REQUEST_GET_VOLTAGE),
		            endpoint_, socket_);

		return receiveMessage(socket_) / 100.0;
	}
}
