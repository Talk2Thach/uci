// Edward Xia   - 73387315
// Amanda Zhang - 79622812

public class CrapsGame {
	private CrapsMetricsMonitor metricsMonitor;
	private int numberOfRolls;

	public CrapsGame(CrapsMetricsMonitor metricsMonitor) {
		this.metricsMonitor = metricsMonitor;
	}

	private int rollDice () {
		return (int)(Math.random() * 6.0 + 1.0) + (int)(Math.random() * 6.0 + 1.0);
	}

	public boolean playGame() {
		boolean result;
		int roll = this.rollDice();
		System.out.println(String.format("Rolled a %d", roll));
		this.numberOfRolls = 1;
		if (roll == 7 || roll == 11) {
			System.out.println("*****Natural! You win!*****");
			metricsMonitor.increaseNaturalCount();
			result = true;
		} else if (roll == 2 || roll == 3 || roll ==12) {
			System.out.println("*****Craps! You loose.*****");
			metricsMonitor.increaseCrapsCount();
			result = false;
		} else {
			int point = roll;
			while (true) {
				roll = this.rollDice();
				System.out.println(String.format("Rolled a %d", roll));
				++this.numberOfRolls;
				if (roll == point) {
					System.out.println("*****Rolled the point! You win!*****");
					result = true;
					break;
				} else if (roll == 7) {
					System.out.println("*****Crap out! You loose.*****");
					result = false;
					break;
				}
			}
		}
		if (this.numberOfRolls > this.metricsMonitor.getMaxRollsInASingleGame()) {
			this.metricsMonitor.setMaxRollsInASingleGame(this.numberOfRolls);
		}
		if (result) {
			this.metricsMonitor.increaseGameWon();
		} else {
			this.metricsMonitor.increaseGameLost();
		}

		this.metricsMonitor.increaseGamePlayed();
		return result;
	}

	public CrapsMetricsMonitor getMetricsMonitor() {
		return metricsMonitor;
	}

	public void setMetricsMonitor(CrapsMetricsMonitor metricsMonitor) {
		this.metricsMonitor = metricsMonitor;
	}

	public int getNumberOfRolls() {
		return numberOfRolls;
	}

	public void setNumberOfRolls(int numberOfRolls) {
		this.numberOfRolls = numberOfRolls;
	}
}
