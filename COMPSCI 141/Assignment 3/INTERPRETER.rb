#!/usr/bin/env ruby

class Parser
  def initialize program
    @program = program.gsub(/#.*$/, "")
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
    @code_segment = []
    parse_statement until @tokens.empty?
    @code_segment
  end

  def parse_statement
    @code_segment.push []

    case @tokens.first
    when "set"
      parse_set
    when "jump"
      parse_jump
    when "jumpt"
      parse_jumpt
    when "halt"
      @code_segment.last.push @tokens.shift
    else
      raise "'set', 'jump', 'jumpt', or 'halt' exptected at #{@tokens.first}"
    end
  end

  def parse_set
    @code_segment.last.push @tokens.shift

    case @tokens.first
    when "write"
      @code_segment.last.push @tokens.shift
    else
      parse_expr
    end

    parse_comma

    case @tokens.first
    when "read"
      @code_segment.last.push @tokens.shift
    else
      parse_expr
    end
  end

  def parse_jump
    @code_segment.last.push @tokens.shift

    parse_expr
  end

  def parse_jumpt
    @code_segment.last.push @tokens.shift

    parse_expr
    parse_comma
    parse_expr
    parse_comparator
    parse_expr
  end

  def parse_expr
    parse_term

    while ['+', '-'].include? @tokens.first
      @code_segment.last.push @tokens.shift
      parse_term
    end
  end

  def parse_term
    parse_factor

    while ['*', '/', '%'].include? @tokens.first
      @code_segment.last.push @tokens.shift
      parse_factor
    end
  end

  def parse_factor
    case @tokens.first
    when "D["
      @code_segment.last.push @tokens.shift

      parse_expr

      case @tokens.first
      when "]"
        @code_segment.last.push @tokens.shift
      else
        raise "']' expected at #{@tokens.first}"
      end
    when "("
      @code_segment.last.push @tokens.shift

      parse_expr

      case @tokens.first
      when ")"
        @code_segment.last.push @tokens.shift
      else
        raise "')' expected at #{@tokens.first}"
      end
    else
      parse_number
    end
  end

  def parse_number
    if @tokens.first =~ /^0|[1-9]\d*$/
      @code_segment.last.push @tokens.shift
    else
      raise "<Number> expected at #{@tokens.first}"
    end
  end

  def parse_comma
    case @tokens.first
    when ","
      @code_segment.last.push @tokens.shift
    else
      raise "',' exptected at #{@tokens.first}"
    end
  end

  def parse_comparator
    case @tokens.first
    when "!=", "==", ">", "<", ">=", "<="
      @code_segment.last.push @tokens.shift
    else
      raise "'!=', '==', '>', '<', '>=', or '<=' expected at #{@tokens.first}"
    end
  end
end



class Interpreter < Parser
  def initialize program
    super
    @C = parse
    @D = Array.new(100) { 0 }
    @PC = 0
    @run_bit = true
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
    case @IR.shift
    when "set"
      execute_set
    when "jump"
      execute_jump
    when "jumpt"
      execute_jumpt
    when "halt"
      @run_bit = false
    end
  end

  def read
    gets.to_i
  end

  def write value
    puts value
  end

  def execute_set
    address = nil

    case @IR.first
    when "write"
      @IR.shift
    else
      address = eval_expr
    end

    @IR.shift

    case @IR.first
    when "read"
      @IR.shift
      value = read
    else
      value = eval_expr
    end

    if address.nil?
      write value
    else
      @D[address] = value
    end
  end

  def execute_jump
    @PC = eval_expr
  end

  def execute_jumpt
    address = eval_expr
    @IR.shift
    left = eval_expr
    op = @IR.shift
    right = eval_expr
    case op
    when "!="
      @PC = address if left != right
    when "=="
      @PC = address if left == right
    when ">="
      @PC = address if left >= right
    when "<="
      @PC = address if left <= right
    when ">"
      @PC = address if left > right
    when "<"
      @PC = address if left < right
    end
  end

  def eval_expr
    value = eval_term

    while ['+', '-'].include? @IR.first
      case @IR.shift
      when '+'
        value = value + eval_term
      when '-'
        value = value - eval_term
      end
    end

    value
  end

  def eval_term
    value = eval_factor

    while ['*', '/', '%'].include? @IR.first
      case @IR.shift
      when '*'
        value = value * eval_factor
      when '/'
        value = value / eval_factor
      when '%'
        value = value % eval_factor
      end
    end

    value
  end

  def eval_factor
    case @IR.first
    when "D["
      @IR.shift
      value = @D[eval_expr]
      @IR.shift
    when "("
      @IR.shift
      value = eval_expr
      @IR.shift
    else
      value = @IR.shift.to_i
    end

    value
  end
end



if __FILE__ == $0
  if ARGV.empty?
    puts "Usage: #{$0} Program.S"
  else
    until ARGV.empty?
      file = File.open ARGV.shift
      Interpreter.new(file.read).run.puts_data_segment
      file.close
    end
  end
end
