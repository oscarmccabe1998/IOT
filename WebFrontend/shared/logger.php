<?php
declare(strict_types=1);

namespace PhpMqtt\Client\Examples\Shared;

use Psr\Log\AbstractLogger;
use Psr\Log\LoggerInterface;
use Psr\Log\LogLevel;

class SimpleLogger extends AbstractLogger implements LoggerInterface
{
    private $logLevel;
    private $logLevelNumeric;
    public function __construct(string $logLevel = null)
    {
        if ($logLevel === null){
            $logLevel = LogLevel::DEBUG;
        }

        $this->logLevel     =$logLevel;
        $this->logLevelNumeric  =$this->mapLogLevelToInteger($logLevel);
    }

    public function log($level, $message, array $context = []): void
    {
        if ($this->mapLogLevelToInteger($level) < $this->logLevelNumeric) {
            return;
        }

        echo $this->interpolate($message, $context) . PHP_EOL;
    }

    private function interpolate($message, array $context = [])
    {
        $replace = [];
        foreach ($context as $key => $val) {
            if (!is_array($val) && (!is_object($val) || method_exists($val, '__toString'))) {
                $replace['{' . $key . '}'] = $val;
            }
        }

        return strtr($message, $replace);
    }

    private function mapLogLevelToInteger(string $level): int
    {
        $map = $this->getLogLevelMap();

        if (!array_key_exists($level, $map)) {
            return $map[LogLevel::DEBUG];
        }

        return $map[$level];
    }
    private function getLogLevelMap(): array
    {
        return [
            LogLevel::DEBUG     => 0,
            LogLevel::INFO      => 1,
            LogLevel::NOTICE    => 2,
            LogLevel::WARNING   => 3,
            LogLevel::ERROR     => 4,
            LogLevel::CRITICAL  => 5,
            LogLevel::ALERT     => 6,
            LogLevel::EMERGENCY => 7,
        ];
    }
}

?>