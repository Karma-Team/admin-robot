
#define CMD_RESET -3
#define SPI_CHANNEL 0
#define SPI_CLOCK_SPEED 1000000

namespace COD
{
	class CSPICodeurManager
	{
		public:

			CSPICodeurManager(char* m_codeurSerieTty);

			virtual ~CSPICodeurManager();

			void initialisation();
			void closeS();

		    void readAndReset();
		    void reset();

			int getRightTicks();
			int getLeftTicks();


		private:
			char m_codeurSerieTty[14];
			int m_leftTicks;
			int m_rightTicks;

	};
}

