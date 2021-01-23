#include "THD_Queue.hpp"
#include "THD_ThreadSafeObject.hpp"

#define PIN_GPIO_SA_DROITE 25 ///< gpio 22
#define PIN_GPIO_SB_DROITE 8  ///< gpio 24

#define PIN_GPIO_SA_GAUCHE 7 ///< gpio 26
#define PIN_GPIO_SB_GAUCHE 1 ///< gpio 28
namespace COD
{
	class CThreadCodeurManager
	{
		public:

			CThreadCodeurManager();

			virtual ~CThreadCodeurManager();

			void initialisation();

		    void reset();

			int getTicksDroit();
			int getTicksGauche();


		private:

			 static void compterTicDroit();
			 static void compterTicGauche();

	};
}

