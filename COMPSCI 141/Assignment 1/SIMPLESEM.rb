#!/usr/bin/env ruby

class Parser
  def initialize program
    @program = program
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
    puts "Program"

    parse_statement until @tokens.empty?
  end

  def parse_statement
    puts "Statement"

    case @tokens.first
    when "set"
      parse_set
    when "jump"
      parse_jump
    when "jumpt"
      parse_jumpt
    when "halt"
      @tokens.shift
    else
      raise "'set', 'jump', 'jumpt', or 'halt' exptected at #{@tokens.first}"
    end
  end

  def parse_set
    puts "Set"

    @tokens.shift

    case @tokens.first
    when "write"
      @tokens.shift
    else
      parse_expr
    end

    parse_comma

    case @tokens.first
    when "read"
      @tokens.shift
    else
      parse_expr
    end
  end

  def parse_jump
    puts "Jump"

    @tokens.shift

    parse_expr
  end

  def parse_jumpt
    puts "Jumpt"

    @tokens.shift

    parse_expr
    parse_comma
    parse_expr
    parse_comparator
    parse_expr
  end

  def parse_expr
    puts "Expr"

    parse_term

    while ['+', '-'].include? @tokens.first
      @tokens.shift
      parse_term
    end
  end

  def parse_term
    puts "Term"

    parse_factor

    while ['*', '/', '%'].include? @tokens.first
      @tokens.shift
      parse_factor
    end
  end

  def parse_factor
    puts "Factor"

    case @tokens.first
    when "D["
      @tokens.shift

      parse_expr

      case @tokens.first
      when "]"
        @tokens.shift
      else
        raise "']' expected at #{@tokens.first}"
      end
    when "("
      @tokens.shift

      parse_expr

      case @tokens.first
      when ")"
        @tokens.shift
      else
        raise "')' expected at #{@tokens.first}"
      end
    else
      parse_number
    end
  end

  def parse_number
    puts "Number"

    if @tokens.first =~ /^0|[1-9]\d*$/
      @tokens.shift
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
    when "!=", "==", ">", "<", ">=", "<="
      @tokens.shift
    else
      raise "'!=', '==', '>', '<', '>=', or '<=' expected at #{@tokens.first}"
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
      Parser.new(file.read).parse
      file.close
    end
  end
end
