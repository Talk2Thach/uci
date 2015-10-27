// Edward Xia   - 73387315
// Amanda Zhang - 79622812

import java.util.Scanner;

public class CrapsSimulation {
	private CrapsGame game;
	private CrapsMetricsMonitor metricsMonitor;
	private String username;
	private int balance;
	private int bet;
	private int winStreak;
	private int loseStreak;

	public void start() {
		Scanner in = new Scanner(System.in);

		while (true) {
			System.out.print("Welcome to SimCraps! Enter your user name: ");
			this.username = in.nextLine();
			System.out.println(String.format("Hello %s!", this.username));
			System.out.print("Enter the amount of money you will bring to the table: ");
			this.balance = in.nextInt();
			this.winStreak = 0;
			this.loseStreak = 0;

			while (this.balance > 0) {
				if (this.game.getMetricsMonitor().getMaxBalance() < this.balance) {
					this.game.getMetricsMonitor().setMaxBalance(this.balance);
					this.game.getMetricsMonitor().setMaxBalanceGameID(this.game.getMetricsMonitor().getGamePlayed() + 1);
				}

				System.out.print(String.format("Enter the bet amount between $1 and $%d: ", this.balance));
				while (true) {
					this.bet = in.nextInt();
					if (this.bet >= 1 && this.bet <= this.balance) {
						break;
					}
					System.out.print(String.format("Invalid bet! Please enter a bet between $1 and $%d: ", this.balance));
				}

				boolean isWinning = game.playGame();
				if (isWinning) {
					this.balance += this.bet;
					this.loseStreak = 0;
					++this.winStreak;
				} else {
					this.balance -= this.bet;
					this.winStreak = 0;
					++this.loseStreak;
				}

				System.out.println(String.format("%s's balance: $%d", this.username, this.balance));

				if (this.game.getMetricsMonitor().getMaxWinningStreak() < this.winStreak) {
					this.game.getMetricsMonitor().setMaxWinningStreak(this.winStreak);
				}

				if (this.game.getMetricsMonitor().getMaxLoseStreak() < this.loseStreak) {
					this.game.getMetricsMonitor().setMaxLoseStreak(this.loseStreak);
				}
			}

			System.out.println();
			this.game.getMetricsMonitor().printStatistics();
			System.out.println();

			in.nextLine(); // clear buffer
			String answer = "";
			while (!(answer.equals("n") || answer.equals("y"))) {
				System.out.print("Replay? Enter 'y' or 'n': ");
				answer = in.nextLine();
			}
			if (answer.equals("n")) {
				break;
			}
			game.getMetricsMonitor().reset();
			System.out.println();
		}
		in.close();
	}

	public CrapsSimulation() {
		this.metricsMonitor = new CrapsMetricsMonitor();
		this.game = new CrapsGame(metricsMonitor);
	}

	public CrapsGame getGame() {
		return game;
	}

	public void setGame(CrapsGame game) {
		this.game = game;
	}

	public CrapsMetricsMonitor getMetricsMonitor() {
		return metricsMonitor;
	}

	public void setMetricsMonitor(CrapsMetricsMonitor metricsMonitor) {
		this.metricsMonitor = metricsMonitor;
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public int getBalance() {
		return balance;
	}

	public void setBalance(int balance) {
		this.balance = balance;
	}

	public int getBet() {
		return bet;
	}

	public void setBet(int bet) {
		this.bet = bet;
	}

	public int getWinStreak() {
		return winStreak;
	}

	public void setWinStreak(int winStreak) {
		this.winStreak = winStreak;
	}

	public int getLoseStreak() {
		return loseStreak;
	}

	public void setLoseStreak(int loseStreak) {
		this.loseStreak = loseStreak;
	}

}
