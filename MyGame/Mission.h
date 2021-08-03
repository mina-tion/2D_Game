class Mission
{
private:
	bool activity;
	bool completeness;	

	int step; 

public:
	Mission();
	virtual ~Mission();

	const bool isActive();
	const bool isComplited();
	const int getStep();


	void comleteMission();
	void setStep(int step);

	void activateMission();
	void deactivateMission();

};

