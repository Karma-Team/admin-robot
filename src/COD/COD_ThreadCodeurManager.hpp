#include "THD_Queue.hpp"
#include "THD_ThreadSafeObject.hpp"

namespace COD
{
	class CThreadCodeurManager
	{
		public:

			CThreadCodeurManager();

			virtual ~CThreadCodeurManager();

			void initialisation();

		    void readAndReset();
		    void reset();

			int getRightTicks();
			int getLeftTicks();


		private:
			int m_leftTicks;
			int m_rightTicks;

	};
}

