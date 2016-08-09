#!/usr/bin/env ruby

class Parser
  def initialize program
    @program = program.gsub(/#.*/, "")
  end

  def tokenize
    tokens = @program.scan %r{
      ==|!=|>=?|<=?|[,*/%+-]|
      [a-zA-Z_]\w*\[?|\]|\(|\)|
      0|[1-9]\d*
    }x

    if (tokens.join + @program.scan(/\s+/).join).length != @program.length
      raise "Unexpected token"
    end

    @tokens = tokens
  end

  def parse
    tokenize
    parse_program
  end

  private

  def parse_program
    code_segment = []
    code_segment.push parse_statement until @tokens.empty?
    code_segment
  end

  def parse_statement
    case @tokens.first
    when "set"
      parse_set
    when "jump"
      parse_jump
    when "jumpt"
      parse_jumpt
    when "halt"
      @tokens.shift
      [:halt]
    else
      raise "'set', 'jump', 'jumpt', or 'halt' exptected at #{@tokens.first}"
    end
  end

  def parse_set
    @tokens.shift

    set = []

    case @tokens.first
    when "write"
      @tokens.shift
      set = [:write]
    else
      set = [:set, parse_expr]
    end

    parse_comma

    case @tokens.first
    when "read"
      @tokens.shift
      set.push [:read]
    else
      set.push parse_expr
    end

    set
  end

  def parse_jump
    @tokens.shift

    [:jump, parse_expr]
  end

  def parse_jumpt
    @tokens.shift

    addr = parse_expr
    parse_comma
    lhs = parse_expr
    op = parse_comparator
    rhs = parse_expr
    [:jumpt, addr, [op, lhs, rhs]]
  end

  def parse_expr
    expr = parse_term

    while ['+', '-'].include? @tokens.first
      case @tokens.shift
      when '+'
        expr = [:add, expr, parse_term]
      when '-'
        expr = [:sub, expr, parse_term]
      end
    end

    expr
  end

  def parse_term
    term = parse_factor

    while ['*', '/', '%'].include? @tokens.first
      case @tokens.shift
      when '*'
        term = [:mul, term, parse_factor]
      when '/'
        term = [:div, term, parse_factor]
      when '%'
        term = [:mod, term, parse_factor]
      end
    end

    term
  end

  def parse_factor
    case @tokens.first
    when "D["
      @tokens.shift

      expr = parse_expr

      case @tokens.first
      when "]"
        @tokens.shift
        [:get, expr]
      else
        raise "']' expected at #{@tokens.first}"
      end
    when "("
      @tokens.shift

      expr = parse_expr

      case @tokens.first
      when ")"
        @tokens.shift
        expr
      else
        raise "')' expected at #{@tokens.first}"
      end
    else
      parse_number
    end
  end

  def parse_number
    if @tokens.first =~ /^0|[1-9]\d*$/
      @tokens.shift.to_i
    else
      raise "<Number> expected at #{@tokens.first}"
    end
  end

  def parse_comma
    case @tokens.first
    when ","
      @tokens.shift
    else
      raise "',' exptected at #{@tokens.first}"
    end
  end

  def parse_comparator
    case @tokens.first
    when "!="
      @tokens.shift
      :ne
    when "=="
      @tokens.shift
      :eq
    when ">"
      @tokens.shift
      :gt
    when "<"
      @tokens.shift
      :lt
    when ">="
      @tokens.shift
      :ge
    when "<="
      @tokens.shift
      :le
    else
      raise "'!=', '==', '>', '<', '>=', or '<=' expected at #{@tokens.first}"
    end
  end
end



class Machine
  def initialize
    reset
  end

  def reset
    @C = []
    @D = Array.new(100) { 0 }
    @PC = 0
    @run_bit = true
    self
  end

  def load program
    @C = Parser.new(program).parse
    self
  end

  def run
    while @run_bit
      fetch
      increment
      execute
    end
    self
  end

  def puts_data_segment
    puts "Data Segment Contents"
    @D.each_index { |i| puts "#{i}: #{@D[i]}"}
  end

  private

  def fetch
    @IR = @C[@PC].dup
  end

  def increment
    @PC = @PC + 1
  end

  def execute
    evaluate @IR
  end

  def evaluate ast
    if ast.is_a? Enumerable
      case ast[0]
      when :add
        evaluate(ast[1]) + evaluate(ast[2])
      when :sub
        evaluate(ast[1]) - evaluate(ast[2])
      when :mul
        evaluate(ast[1]) * evaluate(ast[2])
      when :div
        evaluate(ast[1]) / evaluate(ast[2])
      when :mod
        evaluate(ast[1]) % evaluate(ast[2])
      when :eq
        evaluate(ast[1]) == evaluate(ast[2])
      when :ne
        evaluate(ast[1]) != evaluate(ast[2])
      when :gt
        evaluate(ast[1]) > evaluate(ast[2])
      when :ge
        evaluate(ast[1]) >= evaluate(ast[2])
      when :lt
        evaluate(ast[1]) < evaluate(ast[2])
      when :le
        evaluate(ast[1]) <= evaluate(ast[2])
      when :get
        @D[evaluate(ast[1])]
      when :set
        @D[evaluate(ast[1])] = evaluate(ast[2])
      when :read
        gets.to_i
      when :write
        puts evaluate(ast[1])
      when :jumpt
        @PC = evaluate(ast[1]) if evaluate(ast[2])
      when :jump
        @PC = evaluate(ast[1])
      when :halt
        @run_bit = false
      else
        raise "Invalid AST"
      end
    else
      ast
    end
  end
end



if __FILE__ == $0
  if ARGV.empty?
    puts "Usage: #{$0} Program.S"
  else
    until ARGV.empty?
      $stdout.reopen "#{ARGV.first}.out", "w"
      file = File.open ARGV.shift
      Machine.new
        .load(file.read)
        .run
        .puts_data_segment
      file.close
    end
  end
end
