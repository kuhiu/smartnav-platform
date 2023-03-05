#ifndef D94ED08E_8049_4BBE_9E5F_59107EB7C50D
#define D94ED08E_8049_4BBE_9E5F_59107EB7C50D

namespace Registers {
  const __u8 QMC5883L_X_LSB    = 0x00;
  const __u8 QMC5883L_X_MSB    = 0x01;
  const __u8 QMC5883L_Y_LSB    = 0x02;
  const __u8 QMC5883L_Y_MSB    = 0x03;
  const __u8 QMC5883L_Z_LSB    = 0x04;
  const __u8 QMC5883L_Z_MSB    = 0x05;
  const uint32_t QMC5883L_STATUS   = 0x06;
  const uint32_t QMC5883L_TEMP_LSB = 0x07;
  const uint32_t QMC5883L_TEMP_MSB = 0x08;
  const uint32_t QMC5883L_CONFIG   = 0x09;
  const uint32_t QMC5883L_CONFIG2  = 0x0A;
  const uint32_t QMC5883L_RESET    = 0x0B;
  const uint32_t QMC5883L_RESERVED = 0x0C;
  const uint32_t QMC5883L_CHIP_ID  = 0x0D;

  const uint32_t QMC5883L_STATUS_DRDY = 0x01;
  const uint32_t QMC5883L_STATUS_OVL  = 0x02;
  const uint32_t QMC5883L_STATUS_DOR  = 0x04;
} // namespace CompassRegs


#endif /* D94ED08E_8049_4BBE_9E5F_59107EB7C50D */
