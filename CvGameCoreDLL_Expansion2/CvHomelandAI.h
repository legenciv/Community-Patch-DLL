﻿/*	-------------------------------------------------------------------------------------------------------
	© 1991-2012 Take-Two Interactive Software and its subsidiaries.  Developed by Firaxis Games.  
	Sid Meier's Civilization V, Civ, Civilization, 2K Games, Firaxis Games, Take-Two Interactive Software 
	and their respective logos are all trademarks of Take-Two interactive Software, Inc.  
	All other marks and trademarks are the property of their respective owners.  
	All rights reserved. 
	------------------------------------------------------------------------------------------------------- */
#pragma once

#ifndef CIV5_HOMELAND_AI_H
#define CIV5_HOMELAND_AI_H

#define UPGRADE_THIS_TURN_PRIORITY_BOOST 5000
#define UPGRADE_IN_TERRITORY_PRIORITY_BOOST 2000

struct BuilderDirective;

enum AIHomelandTargetType
{
    AI_HOMELAND_TARGET_NONE,
    AI_HOMELAND_TARGET_CITY,
    AI_HOMELAND_TARGET_SENTRY_POINT,
	AI_HOMELAND_TARGET_SENTRY_POINT_NAVAL,
    AI_HOMELAND_TARGET_FORT,
    AI_HOMELAND_TARGET_NAVAL_RESOURCE,
	AI_HOMELAND_TARGET_WORKER,
	AI_HOMELAND_TARGET_ANTIQUITY_SITE,
};

// Object stored in the list of current move units (m_CurrentMoveUnits)
class CvHomelandUnit
{
public:
	CvHomelandUnit();

	bool operator<(const CvHomelandUnit& unit) const
	{
		return (GetMovesToTarget() < unit.GetMovesToTarget());
	}

	// Accessors
	void SetID(int iID)
	{
		m_iID = iID;
	};
	int GetID() const
	{
		return m_iID;
	};
	void SetMovesToTarget(int iMoves)
	{
		m_iMovesToTarget = iMoves;
	};
	int GetMovesToTarget() const
	{
		return m_iMovesToTarget;
	};
	void SetTarget(CvPlot* pPlot)
	{
		m_pTarget = pPlot;
	};
	CvPlot* GetTarget() const
	{
		return m_pTarget;
	};

	// Stores extra integer data
	//   For potential upgradeable units stores the unit type since that's a convenient way to sort them
	int GetAuxIntData() const
	{
		return m_iAuxData;
	}
	void SetAuxIntData(int iAuxData)
	{
		m_iAuxData = iAuxData;
	}

private:
	int m_iID;
	int m_iAuxData;
	int m_iMovesToTarget;

	CvPlot* m_pTarget;
};

#if defined(MOD_BALANCE_CORE_MILITARY)
//a simple wrapper around std::vector so we can log/break on certain units being added (in a central place)
class CHomelandUnitArray
{
public:
	CHomelandUnitArray() : m_currentHomelandMove(AI_HOMELAND_MOVE_UNASSIGNED) {}

	std::vector<CvHomelandUnit>::iterator begin() { return m_vec.begin(); }
	std::vector<CvHomelandUnit>::iterator end() { return m_vec.end(); }
	std::vector<CvHomelandUnit>::size_type size() const { return m_vec.size(); }
	bool empty() { return m_vec.empty(); }
	std::vector<CvHomelandUnit>::reference operator[](std::vector<CvHomelandUnit>::size_type _Pos) { return m_vec[_Pos]; }
	std::vector<CvHomelandUnit>::iterator erase(std::vector<CvHomelandUnit>::const_iterator _Where) { return m_vec.erase(_Where); }
	void push_back(const CvHomelandUnit& unit);
	void clear() { m_vec.clear(); }
	void setCurrentHomelandMove(AIHomelandMove move) { m_currentHomelandMove=move; }
	AIHomelandMove getCurrentHomelandMove() const { return m_currentHomelandMove; }

	typedef std::vector<CvHomelandUnit>::iterator iterator; 

private:
	std::vector<CvHomelandUnit> m_vec;
	AIHomelandMove m_currentHomelandMove;
};

#endif


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  CLASS:      CvHomelandTarget
//!  \brief		A target of opportunity for the Homeland AI this turn
//
//!  Key Attributes:
//!  - Arises during processing of CvHomelandAI::FindHomelandTargets()
//!  - Targets are reexamined each turn (so shouldn't need to be serialized)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CvHomelandTarget
{
public:

	CvHomelandTarget()
		: m_eTargetType(AI_HOMELAND_TARGET_CITY)
		, m_iTargetX(INVALID_PLOT_COORD)
		, m_iTargetY(INVALID_PLOT_COORD)
		, m_iAuxData(0)
	{
	};

	bool operator<(const CvHomelandTarget& target) const
	{
		return (m_iAuxData > target.m_iAuxData);
	}
	inline AIHomelandTargetType GetTargetType()
	{
		return m_eTargetType;
	}
	inline void SetTargetType(AIHomelandTargetType eTargetType)
	{
		m_eTargetType = eTargetType;
	}
	inline int GetTargetX() const
	{
		return m_iTargetX;
	}
	inline void SetTargetX(int iValue)
	{
		m_iTargetX = iValue;
	}
	inline int GetTargetY() const
	{
		return m_iTargetY;
	}
	inline void SetTargetY(int iValue)
	{
		m_iTargetY = iValue;
	}

	// Used to SORT homeland targets in priority order
	//    Set to the BuildType for improvement targets
	//    Set to the weight for sentry points
	//    Set to the danger for cities to be garrisoned
	inline int GetAuxIntData() const
	{
		return m_iAuxData;
	}
	inline void SetAuxIntData(int iAuxData)
	{
		m_iAuxData = iAuxData;
	}

private:
	AIHomelandTargetType m_eTargetType;
	int m_iTargetX;
	int m_iTargetY;
	int m_iAuxData;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  CLASS:      CvHomelandAI
//!  \brief		A player's AI to control units that are in reserve protecting their lands
//
//!  Key Attributes:
//!  - Handles moves for all military units not recruited by the tactical or operational AI
//!  - Also handles moves for workers and explorers (and settlers on the first turn)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class CvHomelandAI
{
public:
	CvHomelandAI(void);
	~CvHomelandAI(void);
	void Init(CvPlayer* pPlayer);
	void Uninit();
	void Reset();

	// Serialization routines
	template<typename HomelandAI, typename Visitor>
	static void Serialize(HomelandAI& homelandAI, Visitor& visitor);
	void Read(FDataStream& kStream);
	void Write(FDataStream& kStream) const;

	// Public turn update routines
	void RecruitUnits();
	void FindAutomatedUnits();
	void Update(bool bUpdateImprovements);
	void Invalidate();
	bool NeedsUpdate();

	// Public exploration routines
	CvPlot* GetBestExploreTarget(const CvUnit* pUnit, int nMinCandidatesToCheck, int iMaxTurns) const;
	bool ExecuteSpecialExploreMove(CvUnit* pUnit, CvPlot* pTargetPlot);
	bool FindTestArchaeologistPlotPrimer(CvUnit* pUnit);

	// Public logging
	void LogHomelandMessage(const CvString& strMsg);

	bool MoveCivilianToGarrison(CvUnit* pUnit);
	bool MoveCivilianToSafety(CvUnit* pUnit);

	set<int> GetWorkedPlots();

private:
	// Internal turn update routines - commandeered unit processing
	void FindHomelandTargets();
	void AssignHomelandMoves();

	// Routines to manage identifying and implementing homeland moves
	void PlotExplorerMoves();
	void PlotFirstTurnSettlerMoves();
	void PlotHealMoves();
	void PlotMovesToSafety();

	void PlotOpportunisticSettlementMoves();

//------------------------------------- move to tactical AI
#if defined(MOD_BALANCE_CORE)
	void PlotGarrisonMoves();
	void PlotSentryMoves();
	void PlotSentryNavalMoves();
	void PlotPatrolMoves();
	void PlotUpgradeMoves();
	void PlotAircraftRebase();

	void ExecuteUnitGift();
	bool SendUnitGift(DomainTypes eDomain);

	void ExecuteAircraftMoves();
	void ExecutePatrolMoves();

	// Internal low-level utility routines
	void EliminateAdjacentSentryPoints();
	void EliminateAdjacentNavalSentryPoints();

	std::vector<CvHomelandTarget> m_TargetedSentryPoints;
	std::vector<CvHomelandTarget> m_TargetedNavalSentryPoints;
#endif
//-------------------------------------

	void PlanImprovements();
	void PlotWorkerMoves();
	void PlotWriterMoves();
	void PlotArtistMoves();
	void PlotMusicianMoves();
	void PlotScientistMoves();
	void PlotEngineerMoves();
	void PlotGeneralMoves();
	void PlotMerchantMoves();
	void PlotDiplomatMoves();
	void PlotMessengerMoves();
	void PlotProphetMoves();
	void PlotAdmiralMoves();
	void PlotMissionaryMoves();
	void PlotInquisitorMoves();
	void PlotSSPartMoves();
	void PlotTreasureMoves();
	void PlotTradeUnitMoves();
	void PlotArchaeologistMoves();
	void ReviewUnassignedUnits();

	// Routines to execute homeland moves
	void ExecuteFirstTurnSettlerMoves();
	bool ExecuteExplorerMoves(CvUnit* pUnit);

	void ExecuteWorkerMoves();
	void ExecuteMovesToSafestPlot(CvUnit* pUnit);
	bool ExecuteMoveUnitAwayFromBorder(CvUnit* pUnit);
	bool ExecuteMoveToTarget(CvUnit* pUnit, CvPlot* pTarget, int iFlags, bool bEndTurn = false);

	void ExecuteHeals();
	void ExecuteWriterMoves();
	void ExecuteArtistMoves();
	void ExecuteMusicianMoves();
	void ExecuteScientistMoves();
	void ExecuteEngineerMoves();
	void ExecuteGeneralMoves();
	void ExecuteDiplomatMoves();
	void ExecuteMessengerMoves();
	void ExecuteMerchantMoves();
	void ExecuteProphetMoves();
	void ExecuteAdmiralMoves();
	void ExecuteMissionaryMoves();
	void ExecuteInquisitorMoves();
	void ExecuteSSPartMoves();
	void ExecuteTreasureMoves();
	void ExecuteTradeUnitMoves();
	void ExecuteArchaeologistMoves();

	bool FindUnitsForThisMove(AIHomelandMove eMove);
	CvUnit* GetBestUnitToReachTarget(CvPlot* pTarget, int iMaxTurns);
	bool MoveToTargetButDontEndTurn(CvUnit* pUnit, CvPlot* pTargetPlot, int iFlags);

	CvPlot* FindArchaeologistTarget(CvUnit *pUnit);
	vector<OptionWithScore<pair<CvUnit*, BuilderDirective>>> GetWeightedDirectives(
		const vector<BuilderDirective> aDirectives, 
		const set<BuilderDirective> ignoredDirectives, 
		const list<int> allWorkers, 
		const set<int> ignoredWorkers, 
		const std::map<CvUnit*, ReachablePlots>& allWorkersReachablePlots);
	int GetBuilderNumTurnsAway(
		CvUnit* pUnit, 
		BuilderDirective eDirective, 
		const std::map<CvUnit*, ReachablePlots>& allWorkersReachablePlots);

	void UnitProcessed(int iID);
	bool ExecuteCultureBlast(CvUnit* pUnit);
	bool ExecuteGoldenAgeMove(CvUnit* pUnit);
	bool IsValidExplorerEndTurnPlot(const CvUnit* pUnit, CvPlot* pPlot) const;
	void ClearCurrentMoveUnits(AIHomelandMove eNextMove);

	// Logging functions
	CvString GetLogFileName(CvString& playerName) const;

	// Class data
	CvPlayer* m_pPlayer;
	std::list<int> m_CurrentTurnUnits;
	set<int> m_workedPlots;
	list<int> m_greatPeopleForImprovements;
	std::map<UnitAITypes,std::vector<std::pair<int,int>>> m_automatedTargetPlots; //for human units
	bool m_bNeedsUpdate;

	CHomelandUnitArray m_CurrentMoveUnits;

	// Lists of targets for the turn
	std::vector<CvHomelandTarget> m_TargetedCities;
	std::vector<CvHomelandTarget> m_TargetedAntiquitySites;
};

FDataStream& operator>>(FDataStream&, CvHomelandAI&);
FDataStream& operator<<(FDataStream&, const CvHomelandAI&);

#if defined(MOD_BALANCE_CORE_MILITARY)
extern const char* homelandMoveNames[];
extern const char* directiveNames[];
#endif

struct SPatrolTarget {
	CvPlot* pTarget;
	CvPlot* pWorstEnemy; //may be null
	int iThreatLevel;

	SPatrolTarget();
	SPatrolTarget(CvPlot* target, CvPlot* neighbor, int iThreat);
	bool operator<(const SPatrolTarget& rhs) const;
	bool operator==(const SPatrolTarget& rhs) const;
};

struct SBuilderState {
	map<ResourceTypes, int> mExtraResources;
	map<int, FeatureTypes> mChangedPlotFeatures;
	map<int, pair<BuildTypes, ImprovementTypes>> mChangedPlotImprovements;

	SBuilderState(){};
	static const SBuilderState& DefaultInstance() {
		static SBuilderState defaultInstance;
		return defaultInstance;
	}
};

namespace HomelandAIHelpers
{
bool CvHomelandUnitAuxIntSort(const CvHomelandUnit& obj1, const CvHomelandUnit& obj2);
bool CvHomelandUnitAuxIntReverseSort(const CvHomelandUnit& obj1, const CvHomelandUnit& obj2);

int ScoreAirBase(CvPlot* pBasePlot, PlayerTypes ePlayer, bool bDesperate, int iRange);
bool IsGoodUnitMix(CvPlot* pBasePlot, CvUnit* pUnit);
vector<SPatrolTarget> GetPatrolTargets(PlayerTypes ePlayer, bool bWater, int nMaxTargets = 5);

CvPlot* GetPlotForEmbassy(CvUnit* pUnit, CvCity* pCity);
}

#endif //CIV5_HOMELAND_AI_H