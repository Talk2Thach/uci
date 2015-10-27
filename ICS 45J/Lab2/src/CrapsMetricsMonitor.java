// Edward Xia   - 73387315
// Amanda Zhang - 79622812

public class CrapsMetricsMonitor {
	private int gamePlayed;
	private int gameWon;
	private int gameLost;
	private int maxRollsInASingleGame;
	private int naturalCount;
	private int crapsCount;
	private int maxWinningStreak;
	private int maxLoseStreak;
	private int maxBalance;
	private int maxBalanceGameID;

	public void printStatistics() {
		System.out.println(String.format(
				"*****************************\n" +
				"*** SIMULATION STATISTICS ***\n" +
				"*****************************\n" +
				"Games played: %d\n" +
				"Games won: %d\n" +
				"Games lost: %d\n" +
				"Maximum Rolls in a single game: %d\n" +
				"Natural Count: %d\n" +
				"Craps Count: %d\n" +
				"Maximum Winning Streak: %d\n" +
				"Maximum Loosing Streak: %d\n" +
				"Maximum balance: %d during game %d",
				this.gamePlayed,
				this.gameWon,
				this.gameLost,
				this.maxRollsInASingleGame,
				this.naturalCount,
				this.crapsCount,
				this.maxWinningStreak,
				this.maxLoseStreak,
				this.maxBalance,
				this.maxBalanceGameID));
	}

	public void reset() {
		this.gamePlayed = 0;
		this.gameWon = 0;
		this.gameLost = 0;
		this.maxRollsInASingleGame = 0;
		this.naturalCount = 0;
		this.crapsCount = 0;
		this.maxWinningStreak = 0;
		this.maxLoseStreak = 0;
		this.maxBalance = 0;
		this.maxBalanceGameID = 0;
	}

	public int getGamePlayed() {
		return gamePlayed;
	}

	public void setGamePlayed(int gamePlayed) {
		this.gamePlayed = gamePlayed;
	}

	public void increaseGamePlayed() {
		++this.gamePlayed;
	}

	public int getGameWon() {
		return gameWon;
	}

	public void setGameWon(int gameWon) {
		this.gameWon = gameWon;
	}

	public void increaseGameWon() {
		++this.gameWon;
	}

	public int getGameLost() {
		return gameLost;
	}

	public void setGameLost(int gameLost) {
		this.gameLost = gameLost;
	}

	public void increaseGameLost() {
		++this.gameLost;
	}

	public int getMaxRollsInASingleGame() {
		return maxRollsInASingleGame;
	}

	public void setMaxRollsInASingleGame(int maxRollsInASingleGame) {
		this.maxRollsInASingleGame = maxRollsInASingleGame;
	}

	public int getNaturalCount() {
		return naturalCount;
	}

	public void setNaturalCount(int naturalCount) {
		this.naturalCount = naturalCount;
	}

	public void increaseNaturalCount() {
		++this.naturalCount;
	}

	public int getCrapsCount() {
		return crapsCount;
	}

	public void setCrapsCount(int crapsCount) {
		this.crapsCount = crapsCount;
	}

	public void increaseCrapsCount() {
		++this.crapsCount;
	}

	public int getMaxWinningStreak() {
		return maxWinningStreak;
	}

	public void setMaxWinningStreak(int maxWinningStreak) {
		this.maxWinningStreak = maxWinningStreak;
	}

	public int getMaxLoseStreak() {
		return maxLoseStreak;
	}

	public void setMaxLoseStreak(int maxLoseStreak) {
		this.maxLoseStreak = maxLoseStreak;
	}

	public int getMaxBalance() {
		return maxBalance;
	}

	public void setMaxBalance(int maxBalance) {
		this.maxBalance = maxBalance;
	}

	public int getMaxBalanceGameID() {
		return maxBalanceGameID;
	}

	public void setMaxBalanceGameID(int maxBalanceGameID) {
		this.maxBalanceGameID = maxBalanceGameID;
	}
}
